#include "filecopyitem.h"

FileCopyItem::FileCopyItem(QWidget *parent,QStringList* files,QDir filesDir,QDir dest,bool createCopy) : QWidget(parent)
{
    QFont font;

    m_qhblMainLayout = new QHBoxLayout(this);
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

    for (int iFile=0;iFile<files->size();iFile++)
        m_qslFiles.append(files->at(iFile));

    m_qdDest = dest;
    m_qdFilesDir = filesDir;
    m_bCreateCopy = createCopy;
    m_qsCopyResult = "";

    m_tcThreadCopy=nullptr;
    m_repeatClicked=false;
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
        m_pbState->setToolTip("Success");
        m_pbState->setClickable(false);
        disconnect(m_pbState,SIGNAL(clicked(bool)),this,SLOT(repeatSlot()));
    }
    else
    {
        m_pbState->setIconCustom(":/Icon/repeat.png");
        m_pbState->setToolTip("Repeat");
        m_pbState->setClickable(true);
        connect(m_pbState,SIGNAL(clicked(bool)),this,SLOT(repeatSlot()));
    }
    m_qsCopyResult = errorReport;
    m_pbInfo->setToolTip("Informations");
    m_pbInfo->setIconCustom(":/Icon/info.png");

    if (errorReport=="Stopped" || m_repeatClicked)
        emit copyFinished(false,false);
    else
        emit copyFinished(false,true);
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
    QString sourceFile = "";
    QString destFile = "";
    QString errorReport = "";
    QList<QProcess*> processList;

    for (int iFile=0;iFile<m_qslFiles.size();iFile++)
    {
        destFile =  m_qdDest.path()+"/"+m_qslFiles.at(iFile);
        if (destFile.mid(destFile.size()-3) == "exe")
        {
            processList.append(new QProcess(this));
            processList.last()->start(destFile);
        }
    }
    for (int iFile=0;iFile<m_qslFiles.size();iFile++)
    {
        destFile =  m_qdDest.path()+"/"+m_qslFiles.at(iFile);
        if (destFile.mid(destFile.size()-3) == "dll")
        {
            QFile::remove(destFile);
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
    m_repeatClicked=true;
    startCopy();
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
       endSlot("Stopped");
    }
}

void FileCopyItem::infoSlot()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Information");
    msgBox.setIcon(QMessageBox::Information);

    if (m_qsCopyResult.isEmpty())
    {
        msgBox.setText("All files are copied                                           ");       
    }
    else
    {
        msgBox.setText("Error at the time of the copying files                         ");
        msgBox.setDetailedText(m_qsCopyResult);
    }
    msgBox.exec();
}
