#ifndef DEFINE_H
#define DEFINE_H

#endif // DEFINE_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QTime>
#include <QDebug>
#include <QDir>
#include <QProcess>

#define NULLDIR "azertyuiopqsdfghjklmwxcvbn"
#define LOGFILE "Update.log"
#define OLDLOGFILE "Update.old.log"
#define LOGCHECKSIZE 5 // On regarde la taille du log tous les LOGCHECKSIZE fois
#define LOGSIZEMAX 100000 // On fait une action sur le fichier de log s'il est supérieur à LOGSIZEMAX


void addLog(QString log);
bool pingPc(QDir dir);
