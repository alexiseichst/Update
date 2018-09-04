#include "missingfiles.h"

missingFiles::missingFiles(QWidget *parent,QList<QStringList> missingList,QList<QDir> destMissingList) : QDialog(parent)
{
    QPalette pal = palette();
    QPixmap pixmap(":/Icon/warning.png");
    QIcon icon(pixmap);
    QFont font;

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setModal(true);
    setMaximumSize(300,400);
    setMinimumSize(300,400);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("Fichiers manquants");
    setWindowIcon(icon);

    m_missingList = missingList;
    m_destMissingList = destMissingList;

    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qlDestName = new QLabel("");
    m_qlDestName->setAlignment(Qt::AlignCenter);
    font = m_qlDestName->font();
    font.setPointSize(20);
    font.setBold(true);
    m_qlDestName->setFont(font);
    m_qvblMainLayout->addWidget(m_qlDestName);

    m_qlwMissingFilesList = new QListWidget(this);
    m_qvblMainLayout->addWidget(m_qlwMissingFilesList);

    m_qlWidgetItem = new QList<MissingFileItem*>;

    m_qhblButtonLayout = new QHBoxLayout(this);
    m_qvblMainLayout->addLayout(m_qhblButtonLayout);

    m_pbPrevButton = new PushButton(this,":/Icon/left-arrow.png");
    m_pbPrevButton->setMaximumSize(22,22);
    m_pbPrevButton->setIconSize(QSize(22,22));
    m_pbPrevButton->setToolTip("Précédent");
    m_qhblButtonLayout->addWidget(m_pbPrevButton);
    connect(m_pbPrevButton,SIGNAL(clicked(bool)),this,SLOT(prevSlot()));

    m_pbNextButton = new PushButton(this,":/Icon/right-arrow.png");
    m_pbNextButton->setMaximumSize(22,22);
    m_pbNextButton->setIconSize(QSize(22,22));
    m_pbNextButton->setToolTip("Suivant");
    m_qhblButtonLayout->addWidget(m_pbNextButton);
    connect(m_pbNextButton,SIGNAL(clicked(bool)),this,SLOT(nextSlot()));

    m_slIgnoreList = new QList<QList<bool>*>;
    for (int iItem=0;iItem<m_missingList.size();iItem++)
    {
        m_slIgnoreList->append(new QList<bool>);
        for (int iFile=0;iFile<m_missingList.at(iItem).size();iFile++)
            m_slIgnoreList->last()->append(true);
    }

    m_iCurrentIndex=0;
    newDest(m_iCurrentIndex);
}
void missingFiles::newDest(int index)
{
    m_qlWidgetItem->clear();
    m_qlwMissingFilesList->clear();

    m_qlDestName->setText(m_destMissingList.at(index).dirName());
    for (int iItem=0;iItem<m_missingList.at(index).size();iItem++)
    {
        m_qlWidgetItem->append(new MissingFileItem(this,m_missingList.at(index).at(iItem)));
        m_qlWidgetItem->last()->setIgnored(m_slIgnoreList->at(index)->at(iItem));
        m_qlwMissingFilesList->addItem("");
        m_qlwMissingFilesList->setItemWidget(m_qlwMissingFilesList->item(m_qlWidgetItem->size()-1),m_qlWidgetItem->last());
        m_qlwMissingFilesList->item(m_qlWidgetItem->size()-1)->setSizeHint(QSize(m_qlwMissingFilesList->item(m_qlWidgetItem->size()-1)->sizeHint().width(), 50));
    }
    if (m_iCurrentIndex==0)
        m_pbPrevButton->setEnabled(false);
    else
        m_pbPrevButton->setEnabled(true);

    if (m_iCurrentIndex==m_missingList.size()-1)
        m_pbNextButton->setEnabled(false);
    else
        m_pbNextButton->setEnabled(true);
}

void missingFiles::saveDest(int index)
{
    for (int iFile=0;iFile<m_missingList.at(index).size();iFile++)
        m_slIgnoreList->at(index)->replace(iFile,!m_qlWidgetItem->at(iFile)->getIgnored());
}

void missingFiles::prevSlot()
{
    saveDest(m_iCurrentIndex);
    m_iCurrentIndex--;
    newDest(m_iCurrentIndex);
}

void missingFiles::nextSlot()
{
    saveDest(m_iCurrentIndex);
    m_iCurrentIndex++;
    newDest(m_iCurrentIndex);
}
QList<QStringList> missingFiles::getDeleteFiles()
{
    QList<QStringList> rt;

    rt.clear();

    saveDest(m_iCurrentIndex);

    for (int iItem=0;iItem<m_missingList.size();iItem++)
    {
        rt.append(QStringList());
        for (int iFile=0;iFile<m_missingList.at(iItem).size();iFile++)
        {
            if (!m_slIgnoreList->at(iItem)->at(iFile))
                rt.last().append(m_missingList.at(iItem).at(iFile));
        }
    }
    return rt;
}
