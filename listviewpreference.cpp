#include "listviewpreference.h"

ListViewPreference::ListViewPreference(QWidget *parent,QStringList list) : QListWidget(parent)
{
    QAction *tmpAction=nullptr;

    m_qmMenuCR = new QMenu(this);
    m_qmMenuCR->addSeparator();

    tmpAction = m_qmMenuCR->addAction("Ajouter dessus");
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(addAboveSlot()));

    tmpAction = m_qmMenuCR->addAction("Ajouter dessous");
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(addBelowSlot()));

    tmpAction = m_qmMenuCR->addAction("Supprimer");
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(delSlot()));

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));

    for (int item=0;item<list.size();item++)
        addNewItem(item,list.at(item));
}

void ListViewPreference::showMenu(QPoint point)
{
    m_qmMenuCR->exec(mapToGlobal(point));
}

void ListViewPreference::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QListView::currentChanged(current,previous);
}

void ListViewPreference::addAboveSlot()
{
    int row = currentRow();
    addNewItem(row,"Nouveau");

}

void ListViewPreference::addBelowSlot()
{
    int row = currentRow()+1;
    addNewItem(row,"Nouveau");
}

void ListViewPreference::addNewItem(int row,QString txt)
{
    QListWidgetItem *item = new QListWidgetItem();

    item->setFlags(item->flags () | Qt::ItemIsEditable);
    item->setText(txt);
    insertItem(row,item);
}

void ListViewPreference::delSlot()
{
    delete currentItem();
}

