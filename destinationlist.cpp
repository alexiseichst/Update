#include "destinationlist.h"

DestinationList::DestinationList(QWidget *parent) : QListWidget(parent)
{
    m_qlDestItems = new QList<DestinationItem*>;
}

void DestinationList::addNewDir(QDir dir)
{
    m_qlDestItems->append(new DestinationItem(this,dir));
    addItem("");
    connect(m_qlDestItems->last(),SIGNAL(EditClickedSignal(QString)),this,SLOT(EditItemClicked(QString)));
    connect(m_qlDestItems->last(),SIGNAL(DelClickedSignal(QString)),this,SLOT(DelItemClicked(QString)));
    setItemWidget(item(m_qlDestItems->size()-1),m_qlDestItems->last());
    item(m_qlDestItems->size()-1)->setSizeHint(QSize(item(m_qlDestItems->size()-1)->sizeHint().width(), 60));

    for (int iWidjet=0;iWidjet<m_qlDestItems->size();iWidjet++)
    {
         m_qlDestItems->at(iWidjet)->setObjectName(QString::number(iWidjet));
    }
}

void DestinationList::AddItemPopUp()
{
    PopUpNewDestination* NewDestWindows = new PopUpNewDestination();
    NewDestWindows->exec();

    if (NewDestWindows->getQDir())
    {
        addNewDir(*NewDestWindows->getQDir());
    }
    delete NewDestWindows;
}

void DestinationList::EditItemClicked(QString name)
{
    AddItemPopUp();
}

void DestinationList::DelItemClicked(QString name)
{
    int index = name.toInt();

    delete m_qlDestItems->at(index);
    m_qlDestItems->removeAt(index);
    removeItemWidget(item(index));

    for (int iWidjet=0;iWidjet<m_qlDestItems->size();iWidjet++)
    {
         m_qlDestItems->at(iWidjet)->setObjectName(QString::number(iWidjet));
    }
}
