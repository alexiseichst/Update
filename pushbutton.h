#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButton(QWidget *parent = 0,QString icon="");

    void setIconCustom(QString icon);

signals:

public slots:
};

#endif // PUSHBUTTON_H
