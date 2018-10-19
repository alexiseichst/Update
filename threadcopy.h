#ifndef THREADCOPY_H
#define THREADCOPY_H

#include <QObject>
#include <QThread>
#include <QDir>
#include <QStringList>
#include <QDate>
#include <QProcess>

#include "define.h"

class ThreadCopy : public QThread
{
    Q_OBJECT
public:
    explicit ThreadCopy(QObject *parent = 0);
    void setInfos(QDir dest,QDir filesDir,QStringList filesList,bool createCopy);
    void run();
    void stopRun();

private:
    QDir m_qdDest;
    QDir m_qdFilesDir;
    QStringList m_qslFiles;
    bool m_bCreateCopy;
    bool m_bStop;

signals:
    void progressBarValueSignal(int value);
    void endSignal(QString errorReport);

public slots:

};

#endif // THREADCOPY_H
