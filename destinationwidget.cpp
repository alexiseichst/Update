#include "destinationwidget.h"

DestinationWidget::DestinationWidget(QWidget *parent,QList<DESTSELECT> list) : QWidget(parent)
{
    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qvblTopLayout = new QHBoxLayout(m_qvblMainLayout->widget());
    m_qvblMainLayout->addLayout(m_qvblTopLayout);

    m_pbAddButton = new PushButton(this,":/Icon/add.png");
    m_pbAddButton->setToolTip("Ajouter");
    m_qvblTopLayout->addWidget(m_pbAddButton);
    connect(m_pbAddButton,SIGNAL(clicked(bool)),this,SLOT(AddButtonClicked()));
    m_pbAddButton->setMaximumSize(22,22);
    m_pbAddButton->setIconSize(QSize(22,22));

    m_dlDestinationList = new DestinationList(this);
    m_qvblMainLayout->addWidget(m_dlDestinationList);
    connect(m_dlDestinationList,SIGNAL(currentRowChanged(int)),this,SLOT(selectedChange()));
    connect(m_dlDestinationList,SIGNAL(itemSelectionChanged()),this,SLOT(selectedChange()));
    connect(m_dlDestinationList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(selectedChange()));

    for (int iStruc=0;iStruc<list.size();iStruc++)
        m_dlDestinationList->addNewIniDir(list.at(iStruc).dir,list.at(iStruc).id,list.at(iStruc).createCopy);
}

void DestinationWidget::AddButtonClicked()
{
    m_dlDestinationList->AddItemPopUp(-1);
}

void DestinationWidget::selectedChange()
{
    QList<DESTSELECT> signalList = m_dlDestinationList->getSelectedList();
    emit selectedListSignal(signalList);
}
