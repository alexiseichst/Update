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

#ifndef COPYINFOMATION_H
#define COPYINFOMATION_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "define.h"

class CopyInfomation : public QDialog
{
    Q_OBJECT
public:
    explicit CopyInfomation(QWidget *parent = 0,QString result="");

private:
    QString m_qsResult;

    QVBoxLayout* m_qvblMainLayout;

    QLabel* m_qlTitle;
    QTextEdit* m_qteDetail;

    QHBoxLayout* m_qhblButtonsLayout;
    QPushButton* m_qpbExit;

    void boldSrcDest();

signals:
};

#endif // COPYINFOMATION_H
