#include "pushbutton.h"

PushButton::PushButton(QWidget *parent,QString icon) : QPushButton(parent)
{
    QPixmap pixmap(icon);
    QIcon ButtonIcon(pixmap);

    setIcon(ButtonIcon);
    setStyleSheet("QPushButton {border: none;background: transparent;}");
}

void PushButton::setIconCustom(QString icon)
{
    QPixmap pixmap(icon);
    QIcon ButtonIcon(pixmap);

    setIcon(ButtonIcon);
}
