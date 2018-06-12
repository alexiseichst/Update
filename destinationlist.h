#ifndef DESTINATIONLIST_H
#define DESTINATIONLIST_H

#include <QObject>
#include <QListWidget>
#include <QDir>
#include <QList>
#include <QKeyEvent>

#include <destinationitem.h>
#include "popupnewdestination.h"
#include "define.h"

struct DESTSELECT
{
    QDir dir;
    qlonglong id;
    bool selected;
    bool createCopy;
};

class DestinationList : public QListWidget
{
    Q_OBJECT
public:
    explicit DestinationList(QWidget *parent = 0);
    void AddItemPopUp(int index);
    QList<DESTSELECT> getSelectedList();
    void addNewIniDir(QDir dir,qlonglong id,bool createCopy);

private:
    QList<DestinationItem*>* m_qlDestItems;
    QList<QDir> m_qlDir;
    QList<qlonglong> m_qlId;
    QList<bool> m_qlCreateCopy;
    qlonglong m_newId;

    void changeInfos(QDir dir,bool createCopy,int id);
    void addNewDir(QDir dir,bool createCopy);
    void selectOne();

public slots:
    void EditItemClicked(QString name);
    void DelItemClicked(QString name);

};

#endif // DESTINATIONLIST_H
