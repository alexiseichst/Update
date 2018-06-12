#include "destinationwidget.h"

DestinationWidget::DestinationWidget(QWidget *parent) : QWidget(parent)
{
    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qvblTopLayout = new QHBoxLayout(m_qvblMainLayout->widget());
    m_qvblMainLayout->addLayout(m_qvblTopLayout);

    m_pbAddButton = new PushButton(this,":/Icon/add.png");
    m_qvblTopLayout->addWidget(m_pbAddButton);
    connect(m_pbAddButton,SIGNAL(clicked(bool)),this,SLOT(AddButtonClicked()));
    m_pbAddButton->setMinimumSize(22,22);
    m_pbAddButton->setIconSize(QSize(22,22));

    m_dlDestinationList = new DestinationList(this);
    m_qvblMainLayout->addWidget(m_dlDestinationList);

}
void DestinationWidget::AddButtonClicked()
{
    m_dlDestinationList->AddItemPopUp();
}