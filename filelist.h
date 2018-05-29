#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include <QListWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QUrl>
#include <QMimeData>
#include <QDebug>
#include <QCheckBox>
#include <QList>

class FileList : public QListWidget
{
    Q_OBJECT
public:
    explicit FileList(QWidget *parent = 0);

    QList<QCheckBox*>* m_qlCheckBoxList;

    void setList(QStringList list);
    void emptyList();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent  *event);


signals:

public slots:
};

#endif // FILELIST_H
