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

#ifndef DESTINATIONITEM_H
#define DESTINATIONITEM_H

#include <QObject>
#include <QWidget>
#include <QDir>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "pushbutton.h"
#include "define.h"

class DestinationItem : public QWidget
{
    Q_OBJECT
public:
    explicit DestinationItem(QWidget *parent = 0,QDir dir = QDir(NULLDIR),bool createCopy=false);
    void setDir(QDir dir);
    QDir getDir();
    bool getCreateCopy();
    void setCreateCopy(bool createCopy);
    void setCopyOk(bool state);

private:
    QHBoxLayout* m_qvblMainLayout;
    QVBoxLayout* m_qvblButtonLayout;
    QHBoxLayout* m_qvblTextTopLayout;
    QVBoxLayout* m_qvblTextLayout;
    QLabel* m_qlName;
    QLabel* m_qlPath;
    bool m_bCreateCopy;
    PushButton* m_pbEdit;
    PushButton* m_pbDel;
    QDir m_qdDir;

signals:
    void EditClickedSignal(QString name);
    void DelClickedSignal(QString name);

private slots:
    void EditClicked();
    void DelClicked();
};

#endif // DESTINATIONITEM_H
