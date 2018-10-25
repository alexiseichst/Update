#include "destinationlist.h"

DestinationList::DestinationList(QWidget *parent) : QListWidget(parent)
{
    m_qlDestItems = new QList<DestinationItem*>;
    m_newId=0;
}

void DestinationList::addNewDir(QDir dir,bool createCopy)
{ 
    m_qlDestItems->append(new DestinationItem(this,dir,createCopy));
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

void DestinationList::changeInfos(QDir dir,bool createCopy,int index)
{
    m_qlDestItems->at(index)->setDir(dir);
    m_qlDestItems->at(index)->setCreateCopy(createCopy);
}

void DestinationList::AddItemPopUp(int index)
{
    QDir dir = QDir(NULLDIR);
    QDir lastdir = QDir(NULLDIR);
    bool createCopy=false;
    PopUpNewDestination* NewDestWindows = nullptr;

    if (index>=0)
    {
        dir = m_qlDestItems->at(index)->getDir();
        createCopy = m_qlDestItems->at(index)->getCreateCopy();
    }
    else
    {
        if (m_qlDestItems->size()>0)
        {
            lastdir = m_qlDestItems->at(m_qlDestItems->size()-1)->getDir();
        }
    }
    NewDestWindows = new PopUpNewDestination(this,dir,lastdir,createCopy,index==-1?true:false);
    NewDestWindows->exec();

    if (NewDestWindows->getQDir().path() != NULLDIR)
    {
        if (index<0)
        {
            m_qlDir.append(NewDestWindows->getQDir());
            m_qlCreateCopy.append(NewDestWindows->getCreateCopy());
            m_qlId.append(m_newId++);
            addNewDir(NewDestWindows->getQDir(),NewDestWindows->getCreateCopy());
            item(m_qlDir.size()-1)->setSelected(true);
        }
        else
        {
            m_qlDir.replace(index,NewDestWindows->getQDir());
            m_qlCreateCopy.replace(index,NewDestWindows->getCreateCopy());
            changeInfos(NewDestWindows->getQDir(),NewDestWindows->getCreateCopy(),index);
            item(index)->setSelected(true);
            emit itemSelectionChanged();
        }
    }
    if (NewDestWindows)
        delete NewDestWindows;
}

void DestinationList::EditItemClicked(QString name)
{
    AddItemPopUp(name.toInt());
}

void DestinationList::DelItemClicked(QString name)
{
    int index = name.toInt();

    m_qlDir.removeAt(index);
    m_qlId.removeAt(index);
    m_qlCreateCopy.removeAt(index);

    for (int iWidjet=0;iWidjet<m_qlDestItems->size();iWidjet++)
        delete m_qlDestItems->at(iWidjet);

    clear();
    m_qlDestItems->clear();

    for (int iDir=0;iDir<m_qlDir.size();iDir++)
        addNewDir(m_qlDir.at(iDir),m_qlCreateCopy.at(iDir));

    selectOne();
}

QList<DESTSELECT> DestinationList::getSelectedList()
{
    QList<DESTSELECT> returnedList;
    for (int iDir=0;iDir<m_qlDir.size();iDir++)
    {
        DESTSELECT struc;
        struc.dir = m_qlDir.at(iDir);
        struc.selected = item(iDir)->isSelected();
        struc.id = m_qlId.at(iDir);
        struc.createCopy = m_qlCreateCopy.at(iDir);
        returnedList.append(struc);
    }
    return returnedList;
}

void DestinationList::addNewIniDir(QDir dir,qlonglong id,bool createCopy)
{
    m_qlDir.append(dir);
    m_qlId.append(id);
    m_qlCreateCopy.append(createCopy);
    addNewDir(dir,createCopy);
    item(m_qlDir.size()-1)->setSelected(true);
    if (id>=m_newId)
        m_newId=id+1;
}

void DestinationList::selectOne()
{
    if (m_qlDir.size()>0)
        item(m_qlDir.size()-1)->setSelected(true);
}
