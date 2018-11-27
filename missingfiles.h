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

#ifndef MISSINGFILES_H
#define MISSINGFILES_H

#include <QDialog>
#include <QIcon>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>

#include "missingfileitem.h"
#include "pushbutton.h"
#include "define.h"

class missingFiles : public QDialog
{
    Q_OBJECT
public:
    explicit missingFiles(QWidget *parent = 0,QList<QStringList> missingList=QList<QStringList>(),QList<QDir> destMissingList = QList<QDir>());
    QList<QStringList> getDeleteFiles();

private:
    QVBoxLayout *m_qvblMainLayout;
    QLabel *m_qlDestName;
    QList<MissingFileItem*>* m_qlWidgetItem;
    QListWidget *m_qlwMissingFilesList;
    QHBoxLayout *m_qhblButtonLayout;
    PushButton *m_pbPrevButton;
    PushButton *m_pbNextButton;
    int m_iCurrentIndex;
    QList<QStringList> m_missingList;
    QList<QDir> m_destMissingList;
    QList<QList<bool>*>* m_slIgnoreList;

    void newDest(int index);
    void saveDest(int index);

signals:

public slots:
    void prevSlot();
    void nextSlot();
};

#endif // MISSINGFILES_H
