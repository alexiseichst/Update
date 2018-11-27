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

#ifndef POPUPNEWDESTINATION_H
#define POPUPNEWDESTINATION_H

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
#include <QCheckBox>

#include "pushbutton.h"
#include "define.h"

#define LEFT 10
#define TOP 10
#define SPACE 10



class PopUpNewDestination : public QDialog
{
    Q_OBJECT
public:
    explicit PopUpNewDestination(QWidget *parent = 0,QDir dir=QDir(NULLDIR),QDir lastDir=QDir(NULLDIR),bool createCopy=false,bool newDest=true);
    QDir getQDir();
    bool getCreateCopy();

private:
    QVBoxLayout* m_qvblMainLayout;
    QLabel* m_qlName;
    QHBoxLayout* m_qvblPathLayout;
    PushButton* m_qlValidFolderPath;
    QLineEdit* m_qleFolderPath;
    PushButton* m_qpbOpenFolerPath;
    QCheckBox* m_qcbCreateCopy;
    QDialogButtonBox* mqdbButtons;
    QDir m_qdCurrentFolder;
    QDir m_qdLastFolder;
    bool m_bNew;

    void NewFolder(bool setText=false);
    void NewDir(QString path);

private slots:
    void OpenFolerPathClickedSlot();
    void LineFolderPathChangeSlot();
    void DialogBoxButtonSlot(QAbstractButton* button);
    void ExitSlot(bool ok=false);
};

#endif // POPUPNEWDESTINATION_H
