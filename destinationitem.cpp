#include "destinationitem.h"

DestinationItem::DestinationItem(QWidget *parent,QDir dir) : QWidget(parent)
{
    QFont font;

    m_qvblMainLayout = new QHBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qvblTextLayout = new QVBoxLayout(m_qvblMainLayout->widget());
    m_qvblMainLayout->addLayout(m_qvblTextLayout);
    m_qlName = new QLabel(this);
    font = m_qlName->font();
    font.setPointSize(10);
    font.setBold(true);
    m_qlName->setFont(font);
    m_qvblTextLayout->addWidget(m_qlName);
    m_qlPath = new QLabel(this);
     m_qvblTextLayout->addWidget(m_qlPath);

    m_qvblButtonLayout = new QVBoxLayout(m_qvblMainLayout->widget());
    m_qvblMainLayout->addLayout(m_qvblButtonLayout);

    m_pbEdit = new PushButton(this,":/Icon/more.png");
    m_qvblButtonLayout->addWidget(m_pbEdit,0,Qt::AlignRight);
    connect(m_pbEdit,SIGNAL(clicked(bool)),this,SLOT(EditClicked()));

    m_pbDel = new PushButton(this,":/Icon/garbage.png");
    m_qvblButtonLayout->addWidget(m_pbDel,0,Qt::AlignRight);
    connect(m_pbDel,SIGNAL(clicked(bool)),this,SLOT(DelClicked()));

    setDir(dir);
}

void DestinationItem::setDir(QDir dir)
{
    m_qlName->setText(dir.dirName());
    m_qlPath->setText(dir.path());
}
void DestinationItem::EditClicked()
{
    emit EditClickedSignal(this->objectName());
}

void DestinationItem::DelClicked()
{
    emit DelClickedSignal(this->objectName());
}
