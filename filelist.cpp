#include "filelist.h"

FileList::FileList(QWidget *parent) : QListWidget(parent)
{
    m_qlCheckBoxList = new QList<CheckBox*>;
    m_bShiftPressed=false;
    m_iAllDll=-1;
}

void FileList::setList(QStringList list,QList<QIcon> iconList)
{
    m_iAllDll=-1;
    for(int iList=0;iList<list.size();iList++)
    {
        if (list.at(iList)=="Toutes les dll")
            m_iAllDll=iList;

        m_qlCheckBoxList->append(new CheckBox(this,list.at(iList)));
        m_qlCheckBoxList->last()->setObjectName(QString::number(iList));
        m_qlCheckBoxList->last()->setIcon(iconList.at(iList));
        m_qlCheckBoxList->last()->setStyleSheet(" QCheckBox::indicator:checked{image: url(:/Icon/success16.png);}QCheckBox::indicator:unchecked{image: url(:);}");
        addItem("");
        item(m_qlCheckBoxList->size()-1)->setSizeHint(QSize(item(m_qlCheckBoxList->size()-1)->sizeHint().width(), 20));
        setItemWidget(item(iList),m_qlCheckBoxList->at(iList));
        connect(m_qlCheckBoxList->at(iList),SIGNAL(checkStateChangeSignal(QString)),this,SLOT(sendSelectedFilesSlot(QString)));
    }
    selectAllDll();
    emit newFileListSignal();
}

void FileList::sendSelectedFilesSlot(QString name)
{
    QStringList signalList;
    QString txt;
    int index = name.toInt();
    bool state =  m_qlCheckBoxList->at(index)->isChecked();

    if (index==m_iAllDll)
    {
        for(int iCheck=index+1;iCheck<m_qlCheckBoxList->size();iCheck++)
        {
            setCheckedCheckBox(iCheck,state);
            signalList.clear();
            for(int iCheck2=0;iCheck2<m_qlCheckBoxList->size();iCheck2++)
            {
                txt = m_qlCheckBoxList->at(iCheck2)->text();
                if (m_qlCheckBoxList->at(iCheck2)->isChecked() && iCheck2!=m_iAllDll)
                    signalList.append(txt);
            }
            emit sendSelectedFilesSlotSignal(signalList);
        }
    }
    else
    {
        setCheckedCheckBox(index,state);
        selectAllDll();
    }
    signalList.clear();
    for(int iCheck=0;iCheck<m_qlCheckBoxList->size();iCheck++)
    {
        txt = m_qlCheckBoxList->at(iCheck)->text();
        if (m_qlCheckBoxList->at(iCheck)->isChecked() && iCheck!=m_iAllDll)
            signalList.append(txt);
    }

    emit sendSelectedFilesSlotSignal(signalList);
}

void FileList::setSelected(QStringList list)
{
    for(int iCheck=0;iCheck<m_qlCheckBoxList->size();iCheck++)
         setCheckedCheckBox(iCheck,false);

    for(int iList=0;iList<list.size();iList++)
    {
        for(int iCheck=0;iCheck<m_qlCheckBoxList->size();iCheck++)
        {
            if (m_qlCheckBoxList->at(iCheck)->text() == list.at(iList))
            {
                setCheckedCheckBox(iCheck,true);
            }
        }
    }
    selectAllDll();
}

void FileList::selectAllDll()
{
    int index=m_iAllDll;
    bool same=true;
    bool state=true;

    if (m_iAllDll<0)
    {
        return;
    }
    for(int iCheck=index+1;iCheck<m_qlCheckBoxList->size()-1;iCheck++)
    {
        state=m_qlCheckBoxList->at(iCheck)->isChecked();
        if (m_qlCheckBoxList->at(iCheck)->isChecked()!=m_qlCheckBoxList->at(iCheck+1)->isChecked())
        {
            same=false;
            break;
        }
    }
    if (same)
    {
        m_qlCheckBoxList->at(index)->setChecked(state);
    }
    else
    {
         m_qlCheckBoxList->at(index)->setChecked(false);
    }
}

void FileList::emptyList()
{
    int listSize = m_qlCheckBoxList->size();
    for(int iList=0;iList<listSize;iList++)
    {
       m_qlCheckBoxList->last()->hide();
       delete m_qlCheckBoxList->last();
       m_qlCheckBoxList->removeLast();
    }
    clear();
}
void FileList::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
    {
        m_bShiftPressed = true;
    }
}

void FileList::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Shift)
    {
        m_bShiftPressed = false;
    }
}

void FileList::setCheckedCheckBox(int index,bool state)
{
    m_qlCheckBoxList->at(index)->setChecked(state);
    if (state)
        m_qlCheckBoxList->at(index)->setToolTip("Fichier sélectionné");
    else
        m_qlCheckBoxList->at(index)->setToolTip("");
}

void FileList::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void FileList::dragMoveEvent(QDragMoveEvent  *event)
{
    event->accept();
}

void FileList::dropEvent(QDropEvent *event)
{
    QUrl url;
    QString fileName;

    url = event->mimeData()->urls().at(0);
    fileName = url.toLocalFile();

    qDebug() << "Dropped file:" << fileName;
}

QStringList FileList::getFilesList()
{
    QStringList rt;
    QString txt;
    int listSize = m_qlCheckBoxList->size();

    for(int iList=0;iList<listSize;iList++)
    {
       txt = m_qlCheckBoxList->at(iList)->text();

       if (iList!=m_iAllDll)
          rt.append(txt);
    }
    return rt;

}
