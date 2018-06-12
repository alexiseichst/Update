#include "copyfiles.h"

CopyFiles::CopyFiles(QWidget *parent) : QDialog(parent)
{
    QFont font;
    QPalette pal = palette();

    m_qlCopyList=nullptr;
    m_qdFilestDir = QDir(NULLDIR);

    m_qlWidgetItem = new QList<FileCopyItem*>;

    setModal(true);
    setMaximumSize(300,400);
    setMinimumSize(300,400);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("Files copy");

    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qlwFilesCopyList = new QListWidget(this);
    m_qvblMainLayout->addWidget(m_qlwFilesCopyList);
}

void CopyFiles::setStructList(QList<COPYSTRUCT*>* list)
{
    m_qlCopyList = list;

    if (m_qdFilestDir.exists() && m_qlCopyList && m_qlCopyList->size()>0)
    {
        for (int iCopyList=0;iCopyList<m_qlCopyList->size();iCopyList++)
        {
            m_qlWidgetItem->append(new FileCopyItem(this,&m_qlCopyList->at(iCopyList)->FileList,m_qdFilestDir,m_qlCopyList->at(iCopyList)->Destdir,m_qlCopyList->at(iCopyList)->createCopy));
            m_qlwFilesCopyList->addItem("");
            m_qlwFilesCopyList->setItemWidget(m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1),m_qlWidgetItem->last());
            m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1)->setSizeHint(QSize(m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1)->sizeHint().width(), 50));
        }

        for (int iWidjet=0;iWidjet<m_qlWidgetItem->size();iWidjet++)
        {
             m_qlWidgetItem->at(iWidjet)->setObjectName(QString::number(iWidjet));
        }
    }
}

void CopyFiles::setFilesDir(QDir dir)
{
    m_qdFilestDir = dir;
}

void CopyFiles::startCopy()
{
    for (int iWidget=0;iWidget<m_qlWidgetItem->size();iWidget++)
    {
        m_qlWidgetItem->at(iWidget)->startCopy();
    }
}
