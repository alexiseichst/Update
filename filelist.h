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

class FileList : public QListWidget
{
    Q_OBJECT
public:
    explicit FileList(QWidget *parent = 0);
    QList<CheckBox*>* m_qlCheckBoxList;
    void setList(QStringList list,QList<QIcon> iconList);
    void emptyList();
    void setSelected(QStringList list);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent  *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
   bool m_bShiftPressed;

private slots:
    void sendSelectedFilesSlot(QString name);

signals:
    void sendSelectedFilesSlotSignal(QStringList);
    void newFileListSignal();

public slots:
};

#endif // FILELIST_H
