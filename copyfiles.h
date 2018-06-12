#ifndef COPYFILES_H
#define COPYFILES_H

#include <QCoreApplication>
#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>

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
    void startCopy();

private:
    QVBoxLayout* m_qvblMainLayout;
    QList<COPYSTRUCT*>* m_qlCopyList;
    QDir m_qdFilestDir;
    PushButton* m_pbPlayButton;
    QListWidget *m_qlwFilesCopyList;
    QList<FileCopyItem*>* m_qlWidgetItem;
};

#endif // COPYFILES_H
