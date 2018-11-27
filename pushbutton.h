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

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QSize>

#include "define.h"

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = 0,QString icon="",bool clickable=true);
    void setIconCustom(QString icon);
    void setClickable(bool clickable);

    bool m_bClickable;
    QSize m_qsIconSize;

private slots:
    void pressedSlot();
    void releasedSlot();

};

#endif // PUSHBUTTON_H
