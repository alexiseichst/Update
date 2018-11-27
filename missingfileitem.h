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

#ifndef MISSINGFILEITEM_H
#define MISSINGFILEITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>

#include "define.h"

class MissingFileItem : public QWidget
{
    Q_OBJECT
public:
    explicit MissingFileItem(QWidget *parent = 0,QString name="Erreur");

    bool getIgnored();
    void setIgnored(bool ignore);

private:
    QHBoxLayout* m_qhblMainLayout;
    QLabel* m_qlName;
    QPushButton* m_qpbDelete;

signals:

public slots:

private slots:
    void OnDeleteButtonClicked(bool checked);
};

#endif // MISSINGFILEITEM_H
