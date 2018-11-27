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

#ifndef LOADFILEWIDGET_H
#define LOADFILEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QDir>
#include <QtWin>
#include <QFileInfo>
#include <QFileInfoList>
#include <QFileIconProvider>

#include "pushbutton.h"
#include "filelist.h"
#include "define.h"

class LoadFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadFileWidget(QWidget *parent = 0,QString filesDir="");
    void setStringList(QStringList list,bool allExe=false,bool allDll=false);
    void sendSelectedFiles();
    QDir getDir();
    QStringList getFilesList();

private:
    QVBoxLayout* m_qvblMainLayout;
    QHBoxLayout* m_qvblPathLayout;
    QLineEdit* m_qleFolderPath;
    PushButton* m_qpbOpenFolerPath;
    PushButton* m_qlValidFolderPath;
    FileList* m_flFileList;
    QDir m_qdCurrentFolder;
    QStringList* m_qslFileList;
    QString m_qsLastPath;

    void NewFolder();
    void NewDir(QString path);

private slots:
    void OpenFolerPathClickedSlot();
    void LineFolderPathReturnSlot();
    void sendSelectedFilesSlotSlot(QStringList);
    void newFilesListSlot();

signals:
    void sendSelectedFilesSlotSignal(QStringList);
    void newFilesListSignal();
};

#endif // LOADFILEWIDGET_H
