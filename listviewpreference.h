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

#ifndef LISTVIEWPREFERENCE_H
#define LISTVIEWPREFERENCE_H

#include <QListWidget>
#include <QModelIndex>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QStringList>

#include "define.h"

class ListViewPreference : public QListWidget
{
    Q_OBJECT
public:
    explicit ListViewPreference(QWidget *parent = 0,QStringList list=QStringList());

    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
    void addNewItem(int row,QString txt);

private:
    QMenu* m_qmMenuCR;


signals:

public slots:
    void showMenu(QPoint point);
    void addAboveSlot();
    void addBelowSlot();
    void delSlot();
};

#endif // LISTVIEWPREFERENCE_H
