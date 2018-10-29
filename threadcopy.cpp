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
    QFile file;

    tmpCopyList.clear();

    if (m_bStop)
    {
        emit endSignal("Stoppé");
        return;
    }

    if (pingPc(m_qdFilesDir))
    {
        if (!pingPc(m_qdDest))
        {
             errorReport.append("Impossible d'acceder à "+m_qdDest.path());
        }
    }
    else
    {
        errorReport.append("Impossible d'acceder à "+m_qdFilesDir.path());
    }

    if (errorReport.isEmpty() && m_qdFilesDir.exists() && m_qdDest.exists() && m_bCreateCopy)
    {
        addLog("Sauvegarde de "+m_qdDest.path());

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
                    errorReport.append("Impossible de créer la sauvegarde");
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
                errorReport.append("Impossible de créer la sauvegarde");
        }

        if (m_bStop)
        {
            emit endSignal("Stoppé");
            return;
        }

        if (errorReport.isEmpty())
        {
            QString destCopyFile = "";
            tmpCopyList = QStringList(m_qdDest.entryList(QStringList() << "*.*",QDir::Files));

            for (int ifile=0;ifile<tmpCopyList.size();ifile++)
            {
                sourceFile = m_qdDest.path()+"/"+tmpCopyList.at(ifile);
                destCopyFile = destCopyDir.path()+"/"+tmpCopyList.at(ifile);
                file.setFileName(sourceFile);
                if (!file.copy(destCopyFile))
                {

                    errorReport.append("Source: "+sourceFile);
                    errorReport.append("\n");
                    errorReport.append("Dest: "+destCopyFile);
                    errorReport.append("\n");
                    errorReport.append(file.errorString());
                    errorReport.append("\n\n");

                    emit newText("Source: "+sourceFile+"\n"+"Dest: "+destCopyFile+"\n"+file.errorString()+"\n");
                }
                else
                {
                    emit newText("Source: "+sourceFile+"\n"+"Dest: "+destCopyFile+"\nSucess\n");
                    cptFiles++;
                    emit progressBarValueSignal(((float)cptFiles*100.0)/(float)(m_qslFiles.size()+tmpCopyList.size()));
                }
                if (m_bStop)
                {
                    emit endSignal("Stoppé");
                    return;
                }
            }
        }
    }

    if (m_bStop)
    {
        emit endSignal("Stoppé");
        return;
    }

    if (errorReport.isEmpty())
    {
        if (m_qdFilesDir.exists() && m_qdDest.exists())
        {
            addLog("Copie dans "+m_qdDest.path());

            for (int iFile=0;iFile<m_qslFiles.size();iFile++)
            {
                error=false;
                sourceFile = m_qdFilesDir.path()+"/"+m_qslFiles.at(iFile);
                destFile =  m_qdDest.path()+"/"+m_qslFiles.at(iFile);
                file.setFileName(sourceFile);

                if (file.exists(sourceFile))
                {
                    file.setFileName(destFile);
                    if (file.exists())
                        file.remove();

                    if (!file.exists())
                    {
                        file.setFileName(sourceFile);
                        if (!file.copy(destFile))
                            error=true;
                    }
                    else
                    {
                        error=true;
                    }
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
                    errorReport.append("\n");
                    errorReport.append(file.errorString());
                    errorReport.append("\n\n");

                    emit newText("Source: "+sourceFile+"\n"+"Dest: "+destFile+"\n"+file.errorString()+"\n");
                }
                else
                {
                    emit newText("Source: "+sourceFile+"\n"+"Dest: "+destFile+"\nSucess\n");
                    cptFiles++;
                    emit progressBarValueSignal(((float)cptFiles*100.0)/(float)(m_qslFiles.size()+tmpCopyList.size()));
                }
                if (m_bStop)
                {
                    emit endSignal("Stoppé");
                    return;
                }
            }
        }
        else
        {
            if (!m_qdFilesDir.exists())
                errorReport.append("Impossible de trouver le repertoire : "+m_qdFilesDir.path()+"\n");
            if (!m_qdDest.exists())
                errorReport.append("Impossible de trouver le repertoire : "+m_qdDest.path());
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
