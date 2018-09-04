#include "missingfileitem.h"

MissingFileItem::MissingFileItem(QWidget *parent,QString name) : QWidget(parent)
{
    m_qhblMainLayout = new QHBoxLayout(this);

    m_qlName = new QLabel(name,this);
    m_qhblMainLayout->addWidget(m_qlName);

    m_qpbDelete = new QPushButton(this);
    m_qpbDelete->setCheckable(true);
    m_qpbDelete->setText("Ignorer");
    m_qpbDelete->setMaximumWidth(80);
    m_qpbDelete->setMinimumHeight(25);
    m_qpbDelete->setStyleSheet(" QPushButton {border: 2px solid gray;border-radius: 5px;padding: 0 8px;background: transparent;font: bold;}");
    this->connect(m_qpbDelete,SIGNAL(clicked(bool)),SLOT(OnDeleteButtonClicked(bool)));
    m_qhblMainLayout->addWidget(m_qpbDelete);
}

void MissingFileItem::OnDeleteButtonClicked(bool checked)
{
    if (checked)
    {
        m_qpbDelete->setText("Supprimer");
        m_qpbDelete->setStyleSheet(" QPushButton {border: 2px solid gray;border-radius: 5px;padding: 0 8px;background: red;font: bold;}");
    }
    else
    {
        m_qpbDelete->setText("Ignorer");
        m_qpbDelete->setStyleSheet(" QPushButton {border: 2px solid gray;border-radius: 5px;padding: 0 8px;background: transparent;font: bold;}");
    }
}

bool MissingFileItem::getIgnored()
{
    return m_qpbDelete->isChecked();
}

void MissingFileItem::setIgnored(bool ignore)
{
    OnDeleteButtonClicked(!ignore);
}
