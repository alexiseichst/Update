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

#ifndef DESTINATIONWIDGET_H
#define DESTINATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>

#include "pushbutton.h"
#include "destinationlist.h"
#include "define.h"

class DestinationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DestinationWidget(QWidget *parent = 0,QList<DESTSELECT> list = QList<DESTSELECT>());
    void setCopyOk(int index,bool state);

private:
    QVBoxLayout* m_qvblMainLayout;
    QHBoxLayout* m_qvblTopLayout;
    DestinationList* m_dlDestinationList;
    PushButton* m_pbAddButton;

private slots:
    void AddButtonClicked();

public slots:
    void selectedChange();

signals:
    void selectedListSignal(QList<DESTSELECT>);
};

#endif // DESTINATIONWIDGET_H
