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

#ifndef DESTINATIONLIST_H
#define DESTINATIONLIST_H

#include <QObject>
#include <QListWidget>
#include <QDir>
#include <QList>
#include <QKeyEvent>

#include <destinationitem.h>
#include "popupnewdestination.h"
#include "define.h"

struct DESTSELECT
{
    QDir dir;
    qlonglong id;
    bool selected;
    bool createCopy;
};

class DestinationList : public QListWidget
{
    Q_OBJECT
public:
    explicit DestinationList(QWidget *parent = 0);
    void AddItemPopUp(int index);
    QList<DESTSELECT> getSelectedList();
    void addNewIniDir(QDir dir,qlonglong id,bool createCopy);
    void setCopyOk(int index,bool state);

private:
    QList<DestinationItem*>* m_qlDestItems;
    QList<QDir> m_qlDir;
    QList<qlonglong> m_qlId;
    QList<bool> m_qlCreateCopy;
    qlonglong m_newId;

    void changeInfos(QDir dir,bool createCopy,int id);
    void addNewDir(QDir dir,bool createCopy);
    void selectOne();

public slots:
    void EditItemClicked(QString name);
    void DelItemClicked(QString name);

};

#endif // DESTINATIONLIST_H
