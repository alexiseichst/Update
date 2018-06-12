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

    m_pbInfo = new PushButton(this,"");
    m_pbInfo->setMinimumSize(17,17);
    m_pbInfo->setIconSize(QSize(17,17));
    m_qvbRight->addWidget(m_pbInfo);
    connect(m_pbInfo,SIGNAL(clicked(bool)),this,SLOT(infoSlot()));

    m_pbState = new PushButton(this,"");
    m_pbState->setMinimumSize(17,17);
    m_pbState->setIconSize(QSize(17,17));
    m_qvbRight->addWidget(m_pbState);

    for (int iFile=0;iFile<files->size();iFile++)
        m_qslFiles.append(files->at(iFile));

    m_qdDest = dest;
    m_qdFilesDir = filesDir;
    m_bCreateCopy = createCopy;
    m_qsCopyResult = "";
}

void FileCopyItem::startCopy()
{
    QString sourceFile = "";
    QString destFile = "";
    QString errorReport = "";
    QDir destCopyDir;
    bool error=false;
    int cptFiles=0;
    QStringList tmpCopyList;

    tmpCopyList.clear();

    m_qpbProgressBar->setValue(0);
    m_pbState->setIconCustom("");
    m_pbInfo->setIconCustom("");

    if (m_qdFilesDir.exists() && m_qdDest.exists() && m_bCreateCopy)
    {
        QString tmp;
        QString destCopy = m_qdDest.path();

        destCopy.remove(destCopy.size()-1);

        tmp = QString::number(QDate::currentDate().month());
        tmp.size()==1?tmp.insert(0,"0"):tmp=tmp;
        destCopy.append("_"+tmp);

        tmp = QString::number(QDate::currentDate().day());
        tmp.size()==1?tmp.insert(0,"0"):tmp=tmp;
        destCopy.append(tmp);

        tmp = QString::number(QDate::currentDate().year());
        tmp = tmp.mid(2,2);
        destCopy.append(tmp);
        destCopyDir.setPath(destCopy+"/");

        if (destCopyDir.exists())
        {
            int cpt=1;
            QString tmp = destCopyDir.path();
            QDir tmpDir;
            tmp.append("_"+QString::number(cpt));
            tmpDir.setPath(tmp);

            while(tmpDir.exists())
            {
                cpt++;
                tmp = destCopyDir.path();
                tmp.append("_"+QString::number(cpt));
                tmpDir.setPath(tmp);

                if (cpt>=36000)
                    errorReport.append("Impossible to create the copy folder");
            }
            destCopyDir.setPath(tmp);
        }

        if (errorReport.isEmpty())
        {
            QString tmp = destCopyDir.path();
            QDir tmpDir;
            int pos=tmp.size()-1;

            while(tmp.at(pos)!='/')
                pos--;

            tmp = tmp.mid(0,pos);
            tmpDir.setPath(tmp);
            if(!tmpDir.mkdir(destCopyDir.dirName()))
                errorReport.append("Impossible to create the copy folder");
        }

        if (errorReport.isEmpty())
        {
            QString destCopyFile = "";
            tmpCopyList = QStringList(m_qdDest.entryList(QStringList() << "*.*",QDir::Files));

            for (int ifile=0;ifile<tmpCopyList.size();ifile++)
            {
                sourceFile = m_qdDest.path()+"/"+tmpCopyList.at(ifile);
                destCopyFile = destCopyDir.path()+"/"+tmpCopyList.at(ifile);
                if (!QFile::copy(sourceFile,destCopyFile))
                {
                    errorReport.append("Source: "+sourceFile);
                    errorReport.append("\n");
                    errorReport.append("Dest: "+destCopyFile);
                    errorReport.append("\n\n");
                }
                else
                {
                    cptFiles++;
                    m_qpbProgressBar->setValue(((float)cptFiles*100.0)/(float)(m_qslFiles.size()+tmpCopyList.size()));
                }
            }
        }
    }

    if (errorReport.isEmpty())
    {
        if (m_qdDest.exists())
        {
            for (int iFile=0;iFile<m_qslFiles.size();iFile++)
            {
                error=false;
                sourceFile = m_qdFilesDir.path()+"/"+m_qslFiles.at(iFile);
                destFile =  m_qdDest.path()+"/"+m_qslFiles.at(iFile);

                if (QFile::exists(sourceFile))
                {
                    if (QFile::exists(destFile))
                        QFile::remove(destFile);

                    if (!QFile::copy(sourceFile,destFile))
                        error=true;
                }
                else
                {
                    error=true;
                }
                if (error)
                {
                    errorReport.append("Source: "+sourceFile);
                    errorReport.append("\n");
                    errorReport.append("Dest: "+destFile);
                    errorReport.append("\n\n");
                }
                else
                {
                    cptFiles++;
                    m_qpbProgressBar->setValue(((float)cptFiles*100.0)/(float)(m_qslFiles.size()+tmpCopyList.size()));
                }
            }
        }
        else
        {
            errorReport.append("Impossible to find the destination folder : "+m_qdDest.path());
        }
    }
    if (errorReport.isEmpty())
    {
        m_pbState->setIconCustom(":/Icon/success.png");
        m_pbInfo->setIconCustom(":/Icon/info.png");
        disconnect(m_pbState,SIGNAL(clicked(bool)),this,SLOT(repeatSlot()));
    }
    else
    {
        m_pbState->setIconCustom(":/Icon/repeat.png");
        m_pbInfo->setIconCustom(":/Icon/info.png");
        connect(m_pbState,SIGNAL(clicked(bool)),this,SLOT(repeatSlot()));
    }
    m_qsCopyResult = errorReport;
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

void FileCopyItem::repeatSlot()
{
    startCopy();
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
