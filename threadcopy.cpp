#include "threadcopy.h"

ThreadCopy::ThreadCopy(QObject *parent) : QThread(parent)
{
    m_bStop=false;
}

void ThreadCopy::run()
{
    QString sourceFile = "";
    QString destFile = "";
    QString errorReport = "";
    QDir destCopyDir;
    bool error=false;
    int cptFiles=0;
    QStringList tmpCopyList;

    tmpCopyList.clear();

    if (m_bStop)
    {
        emit endSignal("Stopped");
        return;
    }

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
                    emit progressBarValueSignal(((float)cptFiles*100.0)/(float)(m_qslFiles.size()+tmpCopyList.size()));
                }
                if (m_bStop)
                {
                    emit endSignal("Stopped");
                    return;
                }
            }
        }
    }

    if (m_bStop)
    {
        emit endSignal("Stopped");
        return;
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
                    emit progressBarValueSignal(((float)cptFiles*100.0)/(float)(m_qslFiles.size()+tmpCopyList.size()));
                }
                if (m_bStop)
                {
                    emit endSignal("Stopped");
                    return;
                }
            }
        }
        else
        {
            errorReport.append("Impossible to find the destination folder : "+m_qdDest.path());
        }
    }
    emit endSignal(errorReport);
}

void ThreadCopy::setInfos(QDir dest,QDir filesDir,QStringList filesList,bool createCopy)
{
   m_qdDest = dest;
   m_qdFilesDir = filesDir;
   m_qslFiles = filesList;
   m_bCreateCopy = createCopy;
}

void ThreadCopy::stopRun()
{
    m_bStop=true;
}
