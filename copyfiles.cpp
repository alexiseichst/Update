#include "copyfiles.h"

CopyFiles::CopyFiles(QWidget *parent) : QDialog(parent)
{
    QPalette pal = palette();
    QPixmap pixmap(":/Icon/play.png");
    QIcon icon(pixmap);

    m_bRepeat=false;
    m_iCopyIndex=-1;
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
    setWindowIcon(icon);

    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qlwFilesCopyList = new QListWidget(this);
    m_qvblMainLayout->addWidget(m_qlwFilesCopyList);

    m_pbStopButton = new PushButton(this,":/Icon/stop.png",true);
    m_pbStopButton->setToolTip("Stop");
    m_pbStopButton->setMinimumSize(25,25);
    m_pbStopButton->setIconSize(QSize(25,25));
    m_qvblMainLayout->addWidget(m_pbStopButton);
    connect(m_pbStopButton,SIGNAL(clicked(bool)),this,SLOT(stopRepeatCopySlot()));

    m_qtCopyThread = new QThread(this);

}

void CopyFiles::setStructList(QList<COPYSTRUCT*>* list)
{
    m_qlCopyList = list;

    if (m_qdFilestDir.exists() && m_qlCopyList && m_qlCopyList->size()>0)
    {
        for (int iCopyList=0;iCopyList<m_qlCopyList->size();iCopyList++)
        {
            m_qlWidgetItem->append(new FileCopyItem(nullptr,&m_qlCopyList->at(iCopyList)->FileList,m_qdFilestDir,m_qlCopyList->at(iCopyList)->Destdir,m_qlCopyList->at(iCopyList)->createCopy));
            m_qlwFilesCopyList->addItem("");
            m_qlwFilesCopyList->setItemWidget(m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1),m_qlWidgetItem->last());
            m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1)->setSizeHint(QSize(m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1)->sizeHint().width(), 50));
            connect(m_qlWidgetItem->last(),SIGNAL(copyFinished(bool,bool)),SLOT(startCopySlot(bool,bool)));
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

void CopyFiles::globalState()
{
    for (int iCopyIndex=0;iCopyIndex<m_qlWidgetItem->size();iCopyIndex++)
    {
        if(!m_qlWidgetItem->at(iCopyIndex)->getSuccess())
        {
            return;
        }
    }
    m_pbStopButton->setClickable(false);
    m_pbStopButton->setIconCustom(":/Icon/success.png");
    m_pbStopButton->setToolTip("Success");
    disconnect(m_pbStopButton,SIGNAL(clicked(bool)),this,SLOT(stopRepeatCopySlot()));
}

void CopyFiles::startCopySlot(bool first,bool continueCopy)
{
    if (continueCopy)
    {
        if (first)
            m_iCopyIndex=-1;

        m_iCopyIndex++;
        if (m_iCopyIndex<m_qlWidgetItem->size())
        {
            m_qlWidgetItem->at(m_iCopyIndex)->startCopy();
        }
        else
        {
            globalState();
        }
    }
    else
    {
        m_iCopyIndex++;
        if (m_iCopyIndex<m_qlWidgetItem->size())
        {
            m_qlWidgetItem->at(m_iCopyIndex)->stopCopy();
        }
        else
        {
            globalState();
        }
    }
}

void CopyFiles::stopRepeatCopySlot()
{
    if (!m_bRepeat)
    {
        m_qlWidgetItem->at(m_iCopyIndex)->stopCopy();
        m_pbStopButton->setIconCustom(":/Icon/repeat.png");
        m_pbStopButton->setToolTip("Repeat");
    }
    else
    {
        for (int iCopyIndex=0;iCopyIndex<m_qlWidgetItem->size();iCopyIndex++)
            m_qlWidgetItem->at(iCopyIndex)->reset();

        startCopySlot(true,true);
        m_pbStopButton->setIconCustom(":/Icon/stop.png");
        m_pbStopButton->setToolTip("Stop");
    }
    m_bRepeat=!m_bRepeat;
}
