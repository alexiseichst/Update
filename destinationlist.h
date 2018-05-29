#ifndef DESTINATIONLIST_H
#define DESTINATIONLIST_H

#include <QObject>
#include <QListWidget>
#include <QDir>
#include <QList>

#include <destinationitem.h>
#include "popupnewdestination.h"

class DestinationList : public QListWidget
{
    Q_OBJECT
public:
    explicit DestinationList(QWidget *parent = 0);

    void addNewDir(QDir dir);
    void AddItemPopUp();

private:
    QList<DestinationItem*>* m_qlDestItems;

signals:

public slots:
    void EditItemClicked(QString name);
    void DelItemClicked(QString name);

};

#endif // DESTINATIONLIST_H
