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

#ifndef COPYFILES_H
#define COPYFILES_H

#include <QCoreApplication>
#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTimer>
#include <QTextEdit>

#include "settings.h"
#include "pushbutton.h"
#include "filecopyitem.h"
#include "define.h"

class CopyFiles : public QDialog
{
    Q_OBJECT
public:
    explicit CopyFiles(QWidget *parent = 0,bool info=false);
    void setStructList(QList<COPYSTRUCT*>* list);
    void setFilesDir(QDir dir);
    bool getInfo();

private:
    QVBoxLayout* m_qvblMainLayout;
    QList<COPYSTRUCT*>* m_qlCopyList;
    QDir m_qdFilestDir;
    QHBoxLayout* m_qhblButtonLayout;
    PushButton* m_pbStopButton;
    PushButton* m_pbInfoButton;
    PushButton* m_pbDebugButton;
    QListWidget *m_qlwFilesCopyList;
    QList<FileCopyItem*>* m_qlWidgetItem;
    QThread* m_qtCopyThread;
    QTextEdit* m_qteDetail;
    int m_iCopyIndex;
    bool m_bRepeat;
    bool m_bSuccess;
    bool m_bInfos;

    void globalState();

public slots:
    void startCopySlot(bool first,bool continueCopy);
    void stopRepeatCopySlot();
    void infoCopySlot();
    void newTextSlot(QString txt);
};

#endif // COPYFILES_H
