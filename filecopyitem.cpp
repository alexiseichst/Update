#include "filecopyitem.h"

FileCopyItem::FileCopyItem(QWidget *parent,QStringList* files,QDir filesDir,QDir dest,bool createCopy) : QWidget(parent)
{
    QFont font;

    m_qhblMainLayout = new QHBoxLayout();
    this->setLayout(m_qhblMainLayout);

    m_qvbLeft= new QVBoxLayout();
    m_qhblMainLayout->addLayout(m_qvbLeft);
    m_qlName = new QLabel(dest.dirName(),this);
    font.setBold(true);
    m_qlName->setFont(font);
    m_qvbLeft->addWidget(m_qlName);
    m_qpbProgressBar = new QProgressBar(this);
    m_qvbLeft->addWidget(m_qpbProgressBar);
    m_qpbProgressBar->setMaximumHeight(10);
    m_qpbProgressBar->setValue(0);

    m_qvbRight= new QVBoxLayout();
    m_qhblMainLayout->addLayout(m_qvbRight);

    m_pbInfo = new PushButton(this,"",true);
    m_pbInfo->setMinimumSize(17,17);
    m_pbInfo->setIconSize(QSize(17,17));
    m_qvbRight->addWidget(m_pbInfo);
    connect(m_pbInfo,SIGNAL(clicked(bool)),this,SLOT(infoSlot()));

    m_pbState = new PushButton(this,"",false);
    m_pbState->setMinimumSize(17,17);
    m_pbState->setIconSize(QSize(17,17));
    m_qvbRight->addWidget(m_pbState);
    connect(m_pbState,SIGNAL(clicked(bool)),this,SLOT(repeatSlot()));

    for (int iFile=0;iFile<files->size();iFile++)
        m_qslFiles.append(files->at(iFile));

    m_qdDest = dest;
    m_qdFilesDir = filesDir;
    m_bCreateCopy = createCopy;
    m_qsCopyResult = "";

    m_tcThreadCopy=nullptr;
    m_repeatClicked=false;
    m_repeatOk=false;
}

FileCopyItem::~FileCopyItem()
{
   stopCopy();
}

void FileCopyItem::endSlot(QString errorReport)
{
    if (errorReport.isEmpty())
    {
        m_pbState->setIconCustom(":/Icon/success.png");
        m_pbState->setToolTip("Terminé");
        m_repeatOk=false;
        //deleteDll();
    }
    else
    {
        m_pbState->setIconCustom(":/Icon/repeat.png");
        m_pbState->setToolTip("Recommencer");
        m_repeatOk=true;

    }
    m_qsCopyResult = errorReport;
    m_pbInfo->setToolTip("Informations");
    m_pbInfo->setIconCustom(":/Icon/info.png");

    if (errorReport=="Stoppé" || m_repeatClicked)
        emit copyFinished(false,false);
    else
        emit copyFinished(false,true);

    m_repeatClicked=false;
}

void FileCopyItem::startCopy()
{
    reset();
    if (m_tcThreadCopy==nullptr)
    {
        m_tcThreadCopy = new ThreadCopy();
        m_tcThreadCopy->setInfos(m_qdDest,m_qdFilesDir,m_qslFiles,m_bCreateCopy);
        connect(m_tcThreadCopy,SIGNAL(progressBarValueSignal(int)),m_qpbProgressBar,SLOT(setValue(int)));
        connect(m_tcThreadCopy,SIGNAL(endSignal(QString)),this,SLOT(endSlot(QString)));
    }
    else
    {
       stopCopy();
       startCopy();
    }
    m_tcThreadCopy->start();
}

void FileCopyItem::deleteDll()
{
    bool deleteAll=true;
    QString destFile = "";
    QList<QProcess*> processList;

    for (int iFile=0;iFile<m_qslFiles.size();iFile++)
    {
        destFile =  m_qdDest.path()+"/"+m_qslFiles.at(iFile);
        if (destFile.mid(destFile.size()-3) == "exe")
        {
            processList.append(new QProcess(this));
            processList.last()->start(destFile);
            thread()->msleep(100);
        }
    }

    thread()->msleep(1000);
    for (int iFile=0;iFile<processList.size();iFile++)
    {
        if (processList.at(iFile)->state()!=QProcess::Running)
        {
            deleteAll=false;
        }
    }
    thread()->msleep(1000);

    if (deleteAll)
    {
        for (int iFile=0;iFile<m_qslFiles.size();iFile++)
        {
            destFile =  m_qdDest.path()+"/"+m_qslFiles.at(iFile);
            if (destFile.mid(destFile.size()-3) == "dll")
            {
                QFile::remove(destFile);
            }
        }
    }

    for (int iFile=0;iFile<processList.size();iFile++)
    {
        processList.at(iFile)->kill();
    }

    processList.clear();
}

void FileCopyItem::reset()
{
    m_qpbProgressBar->setValue(0);
    m_pbState->setIconCustom("");
    m_pbState->setToolTip("");
    m_pbInfo->setIconCustom("");
    m_pbInfo->setToolTip("");
}

void FileCopyItem::repeatSlot()
{
    if (m_repeatOk)
    {
        m_repeatClicked=true;
        startCopy();
    }
    else
    {
        m_pbState->setIconCustom(":/Icon/repeat.png");
        m_pbState->setToolTip("Recommencer");
        m_repeatOk=true;
    }
}

bool FileCopyItem::getSuccess()
{
    if (m_qsCopyResult.isEmpty())
        return true;
    else
        return false;
}

void FileCopyItem::stopCopy()
{
    int timout=0;

    if (m_tcThreadCopy)
    {
        m_tcThreadCopy->stopRun();
        while (m_tcThreadCopy->isRunning() && timout<10)
        {
            this->thread()->msleep(100);
            timout++;
        }
        delete m_tcThreadCopy;
        m_tcThreadCopy=nullptr;
    }
    else
    {
       endSlot("Stoppé");
    }

}

void FileCopyItem::infoSlot()
{
    CopyInfomation information(this,m_qsCopyResult);
    information.exec();
}
