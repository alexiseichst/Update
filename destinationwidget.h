#ifndef DESTINATIONWIDGET_H
#define DESTINATIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>

#include "pushbutton.h"
#include "destinationlist.h"
#include "define.h"

class DestinationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DestinationWidget(QWidget *parent = 0,QList<DESTSELECT> list = QList<DESTSELECT>());

private:
    QVBoxLayout* m_qvblMainLayout;
    QHBoxLayout* m_qvblTopLayout;
    DestinationList* m_dlDestinationList;
    PushButton* m_pbAddButton;

private slots:
    void AddButtonClicked();

public slots:
    void selectedChange();

signals:
    void selectedListSignal(QList<DESTSELECT>);
};

#endif // DESTINATIONWIDGET_H
