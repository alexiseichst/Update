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

#ifndef ABOUT_H
#define ABOUT_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include <QFileDialog>
#include <QVersionNumber>

#include "pushbutton.h"
#include "define.h"

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0);

private:
    QVBoxLayout* m_qvblMainLayout;

    QLabel* m_qlVersion;
    QVersionNumber m_qvnVersion;
    PushButton* m_pbLogo;

private slots:

};

#endif // ABOUT_H
