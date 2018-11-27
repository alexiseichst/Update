// This file is part of Update.

//  Update is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  any later version.

//  Update is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with Update.  If not, see <https://www.gnu.org/licenses/>.

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
    void newText(QString txt);

public slots:

};

#endif // THREADCOPY_H
