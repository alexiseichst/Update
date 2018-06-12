#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>

class CheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit CheckBox(QWidget *parent = 0,QString text="");

signals:
    void checkStateChangeSignal(QString name);

public slots:
    void checkStateChangeSlot();
};

#endif // CHECKBOX_H
