#include "checkbox.h"

CheckBox::CheckBox(QWidget *parent,QString text) : QCheckBox(parent)
{
    setText(text);
    connect(this,SIGNAL(clicked(bool)),this,SLOT(checkStateChangeSlot()));
}

void CheckBox::checkStateChangeSlot()
{
    emit checkStateChangeSignal(objectName());
}
