#include "filelist.h"

FileList::FileList(QWidget *parent) : QListWidget(parent)
{
    setAcceptDrops(true);

    m_qlCheckBoxList = new QList<QCheckBox*>;
}

void FileList::setList(QStringList list)
{
    for(int iList=0;iList<list.size();iList++)
    {
        addItem("");
        m_qlCheckBoxList->append(new QCheckBox(list.at(iList)));
        setItemWidget(item(iList),m_qlCheckBoxList->at(iList));
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
