#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QSize>

#include "define.h"

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = 0,QString icon="",bool clickable=true);
    void setIconCustom(QString icon);

    bool m_bClickable;
    QSize m_qsIconSize;

private slots:
    void pressedSlot();
    void releasedSlot();

};

#endif // PUSHBUTTON_H
