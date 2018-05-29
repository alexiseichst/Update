#ifndef DESTINATIONWIDGET_H
#define DESTINATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "pushbutton.h"
#include "destinationlist.h"

class DestinationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DestinationWidget(QWidget *parent = 0);

private:
    QVBoxLayout* m_qvblMainLayout;
    QHBoxLayout* m_qvblTopLayout;

    DestinationList* m_dlDestinationList;

    PushButton* m_pbAddButton;

signals:

private slots:
    void AddButtonClicked();
};

#endif // DESTINATIONWIDGET_H
