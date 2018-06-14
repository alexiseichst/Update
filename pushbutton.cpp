#include "pushbutton.h"

PushButton::PushButton(QWidget *parent,QString icon,bool clickable) : QPushButton(parent)
{
    QPixmap pixmap(icon);
    QIcon ButtonIcon(pixmap);

    setIcon(ButtonIcon);
    setStyleSheet("QPushButton {border: none;background: transparent;}");

    m_bClickable = clickable;

    this->connect(this,SIGNAL(pressed()),SLOT(pressedSlot()));
    this->connect(this,SIGNAL(released()),SLOT(releasedSlot()));
}

void PushButton::setIconCustom(QString icon)
{
    QPixmap pixmap(icon);
    QIcon ButtonIcon(pixmap);

    setIcon(ButtonIcon);
}
void PushButton::pressedSlot()
{
    if (m_bClickable)
    {
        setFixedSize(size());
        m_qsIconSize = iconSize();
        setIconSize(QSize(m_qsIconSize.width()-4,m_qsIconSize.height()-4));
    }
}

void PushButton::releasedSlot()
{
    if (m_bClickable)
    {
        setIconSize(m_qsIconSize);
    }

}

void PushButton::setClickable(bool clickable)
{
    m_bClickable = clickable;
}
