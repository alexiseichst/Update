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
