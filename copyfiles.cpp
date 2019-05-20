#include "copyfiles.h"

CopyFiles::CopyFiles(QWidget *parent,bool info) : QDialog(parent)
{
    addLog("Lancement d'une copie");

    QPalette pal = palette();
    QPixmap pixmap(":/Icon/play.png");
    QIcon icon(pixmap);

    m_bRepeat=false;
    m_bSuccess=false;
    m_iCopyIndex=-1;
    m_qlCopyList=nullptr;
    m_qdFilestDir = QDir(NULLDIR);

    m_qlWidgetItem = new QList<FileCopyItem*>;

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setModal(true);
    setMaximumSize(300,400);
    setMinimumSize(300,400);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("Copie des fichiers");
    setWindowIcon(icon);

    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qlwFilesCopyList = new QListWidget(this);
    m_qvblMainLayout->addWidget(m_qlwFilesCopyList);

    m_qteDetail=new QTextEdit(this);
    m_qvblMainLayout->addWidget(m_qteDetail);
    m_qteDetail->setStyleSheet("QTextEdit {color: lime; background-color: black}");
    m_qteDetail->setReadOnly(true);
    m_qteDetail->hide();
    m_bInfos=false;

    m_qhblButtonLayout = new QHBoxLayout();
    m_qvblMainLayout->addLayout(m_qhblButtonLayout);

    m_pbDebugButton = new PushButton(this,"",true);
    m_pbDebugButton->setToolTip("Details");
    m_pbDebugButton->setMaximumSize(20,20);
    m_pbDebugButton->setIconSize(QSize(20,20));
    m_pbDebugButton->setEnabled(false);
    m_qhblButtonLayout->addWidget(m_pbDebugButton,0,Qt::AlignLeft);

    m_pbStopButton = new PushButton(this,":/Icon/stop.png",true);
    m_pbStopButton->setToolTip("Stop");
    m_pbStopButton->setMaximumSize(25,25);
    m_pbStopButton->setIconSize(QSize(25,25));
    m_qhblButtonLayout->addWidget(m_pbStopButton,0,Qt::AlignCenter);
    connect(m_pbStopButton,SIGNAL(clicked(bool)),this,SLOT(stopRepeatCopySlot()));

    m_pbInfoButton = new PushButton(this,":/Icon/info.png",true);
    m_pbInfoButton->setToolTip("Details");
    m_pbInfoButton->setMaximumSize(20,20);
    m_pbInfoButton->setIconSize(QSize(20,20));
    m_qhblButtonLayout->addWidget(m_pbInfoButton,0,Qt::AlignRight);
    connect(m_pbInfoButton,SIGNAL(clicked(bool)),this,SLOT(infoCopySlot()));

    m_qtCopyThread = new QThread(this);

    m_bInfos=!info;
    infoCopySlot();
}

void CopyFiles::setStructList(QList<COPYSTRUCT*>* list)
{
    QListWidgetItem* item=NULL;
    m_qlCopyList = list;

    if (pingPc(m_qdFilestDir) && m_qdFilestDir.exists() && m_qlCopyList && m_qlCopyList->size()>0)
    {
        for (int iCopyList=0;iCopyList<m_qlCopyList->size();iCopyList++)
        {
            m_qlWidgetItem->append(new FileCopyItem(nullptr,&m_qlCopyList->at(iCopyList)->FileList,m_qdFilestDir,m_qlCopyList->at(iCopyList)->Destdir,m_qlCopyList->at(iCopyList)->createCopy));
            m_qlwFilesCopyList->addItem("");
            item = m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1);
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable);

            m_qlwFilesCopyList->setItemWidget(item,m_qlWidgetItem->last());
            connect(m_qlWidgetItem->last(),SIGNAL(copyFinished(bool,bool)),SLOT(startCopySlot(bool,bool)));
            connect(m_qlWidgetItem->last(),SIGNAL(newText(QString)),SLOT(newTextSlot(QString)));

            item->setSizeHint(QSize(m_qlwFilesCopyList->item(m_qlWidgetItem->size()-1)->sizeHint().width(), 50));
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
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
            m_bRepeat=true;
            m_pbStopButton->setIconCustom(":/Icon/repeat.png");
            m_pbStopButton->setToolTip("Recommencer");
            return;
        }
    }
    m_bSuccess=true;
    m_pbStopButton->setClickable(false);
    m_pbStopButton->setIconCustom(":/Icon/success.png");
    m_pbStopButton->setToolTip("Terminé");
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
    if (!m_bRepeat  && !m_bSuccess)
    {
        m_qlWidgetItem->at(m_iCopyIndex < m_qlWidgetItem->size()-1 ? m_iCopyIndex : m_qlWidgetItem->size()-1)->stopCopy();
        m_pbStopButton->setIconCustom(":/Icon/repeat.png");
        m_pbStopButton->setToolTip("Recommencer");
        m_bRepeat = true;
    }
    else if (m_bRepeat && !m_bSuccess)
    {
        for (int iCopyIndex=0;iCopyIndex<m_qlWidgetItem->size();iCopyIndex++)
            m_qlWidgetItem->at(iCopyIndex)->reset();

        startCopySlot(true,true);
        m_pbStopButton->setIconCustom(":/Icon/stop.png");
        m_pbStopButton->setToolTip("Stop");
        m_qteDetail->clear();
        m_bRepeat = false;
    }
    else
    {
        m_pbStopButton->setIconCustom(":/Icon/repeat.png");
        m_pbStopButton->setToolTip("Terminé");
        m_bSuccess=false;
        m_bRepeat = true;
    }
}

void CopyFiles::infoCopySlot()
{
    if (m_bInfos)
    {
        setMaximumSize(300,400);
        setMinimumSize(300,400);
        resize(300,400);
        m_qteDetail->hide();
    }
    else
    {
        setMaximumSize(400,500);
        setMinimumSize(400,500);
        resize(400,500);
        m_qteDetail->show();
    }
    m_bInfos=!m_bInfos;
}

void CopyFiles::newTextSlot(QString txt)
{
    m_qteDetail->append(txt);
}

bool CopyFiles::getInfo()
{
    return m_bInfos;
}
