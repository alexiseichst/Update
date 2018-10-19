#ifndef LISTVIEWPREFERENCE_H
#define LISTVIEWPREFERENCE_H

#include <QListWidget>
#include <QModelIndex>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QStringList>

#include "define.h"

class ListViewPreference : public QListWidget
{
    Q_OBJECT
public:
    explicit ListViewPreference(QWidget *parent = 0,QStringList list=QStringList());

    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
    void addNewItem(int row,QString txt);

private:
    QMenu* m_qmMenuCR;


signals:

public slots:
    void showMenu(QPoint point);
    void addAboveSlot();
    void addBelowSlot();
    void delSlot();
};

#endif // LISTVIEWPREFERENCE_H
