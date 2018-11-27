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

#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QDir>
#include <QtWinExtras>

#include "define.h"
#include "checkbox.h"

#define ALLDLLNAME "Toutes les dll"

class FileList : public QListWidget
{
    Q_OBJECT
public:
    explicit FileList(QWidget *parent = 0);
    QList<CheckBox*>* m_qlCheckBoxList;
    void setList(QStringList list,QList<QIcon> iconList);
    void emptyList();
    void setSelected(QStringList list,bool allExe=false,bool allDll=false);
    QStringList getFilesList();
    void sendSelectedFiles();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent  *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
   bool m_bShiftPressed;
   int m_iAllDll;

   void setCheckedCheckBox(int index,bool state);
   void selectAllDll();
   bool selectFile(QString name1,QString name2,bool allExe,bool allDll);

private slots:
    void sendSelectedFilesSlot(QString name);

signals:
    void sendSelectedFilesSlotSignal(QStringList);
    void newFileListSignal();

public slots:
};

#endif // FILELIST_H
