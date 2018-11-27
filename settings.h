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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QRect>
#include <QList>
#include <QDir>

#include "define.h"

struct COPYSTRUCT
{
    QDir Destdir;
    QStringList FileList;
    qlonglong Id;
    bool createCopy;
};

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    void save(QRect *windowsRect,QList<COPYSTRUCT*>* list,QString filesDir);
    void load(QRect *windowsRect,QList<COPYSTRUCT*>* list,QString* filesDir);

private:
    QSettings* m_qsSettings;
};

#endif // SETTINGS_H
