#ifndef COPYFILES_H
#define COPYFILES_H

#include <QCoreApplication>
#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTimer>

#include "settings.h"
#include "pushbutton.h"
#include "filecopyitem.h"
#include "define.h"

class CopyFiles : public QDialog
{
    Q_OBJECT
public:
    explicit CopyFiles(QWidget *parent = 0);
    void setStructList(QList<COPYSTRUCT*>* list);
    void setFilesDir(QDir dir);

private:
    QVBoxLayout* m_qvblMainLayout;
    QList<COPYSTRUCT*>* m_qlCopyList;
    QDir m_qdFilestDir;
    PushButton* m_pbStopButton;
    QListWidget *m_qlwFilesCopyList;
    QList<FileCopyItem*>* m_qlWidgetItem;
    QThread* m_qtCopyThread;
    int m_iCopyIndex;
    bool m_bRepeat;

    void globalState();

public slots:
    void startCopySlot(bool first,bool continueCopy);
    void stopRepeatCopySlot();
};

#endif // COPYFILES_H
