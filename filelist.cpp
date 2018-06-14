#include "filelist.h"

FileList::FileList(QWidget *parent) : QListWidget(parent)
{
    m_qlCheckBoxList = new QList<CheckBox*>;
    m_bShiftPressed=false;
}

void FileList::setList(QStringList list,QList<QIcon> iconList)
{
    for(int iList=0;iList<list.size();iList++)
    {         
        m_qlCheckBoxList->append(new CheckBox(this,list.at(iList)));
        m_qlCheckBoxList->last()->setObjectName(QString::number(iList));
        m_qlCheckBoxList->last()->setIcon(iconList.at(iList));
        m_qlCheckBoxList->last()->setStyleSheet(" QCheckBox::indicator:checked{image: url(:/Icon/success16.png);}QCheckBox::indicator:unchecked{image: url(:);}");
        addItem("");
        item(m_qlCheckBoxList->size()-1)->setSizeHint(QSize(item(m_qlCheckBoxList->size()-1)->sizeHint().width(), 20));
        setItemWidget(item(iList),m_qlCheckBoxList->at(iList));
        connect(m_qlCheckBoxList->at(iList),SIGNAL(checkStateChangeSignal(QString)),this,SLOT(sendSelectedFilesSlot(QString)));
    }
    emit newFileListSignal();
}

void FileList::sendSelectedFilesSlot(QString name)
{
    QStringList signalList;
    int index = name.toInt();
    bool state =  m_qlCheckBoxList->at(index)->isChecked();

    if (m_bShiftPressed)
    {
        for(int iCheck=index-1;iCheck>=0;iCheck--)
        {
            if (m_qlCheckBoxList->at(iCheck)->isChecked() != state)
                setCheckedCheckBox(iCheck,state);
            else
                break;
        }
    }

    for(int iCheck=0;iCheck<m_qlCheckBoxList->size();iCheck++)
    {
        if (m_qlCheckBoxList->at(iCheck)->isChecked())
            signalList.append(m_qlCheckBoxList->at(iCheck)->text());
    }
    emit sendSelectedFilesSlotSignal(signalList);
}

void FileList::setSelected(QStringList list)
{
    for(int iCheck=0;iCheck<m_qlCheckBoxList->size();iCheck++)
         setCheckedCheckBox(iCheck,false);

    for(int iCheck=0;iCheck<m_qlCheckBoxList->size();iCheck++)
    {
        for(int iList=0;iList<list.size();iList++)
        {
            if (m_qlCheckBoxList->at(iCheck)->text() == list.at(iList))
                setCheckedCheckBox(iCheck,true);
        }
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
        m_qlCheckBoxList->at(index)->setToolTip("File selected");
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
