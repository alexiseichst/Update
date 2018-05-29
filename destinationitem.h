#ifndef DESTINATIONITEM_H
#define DESTINATIONITEM_H

#include <QObject>
#include <QWidget>
#include <QDir>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "pushbutton.h"

class DestinationItem : public QWidget
{
    Q_OBJECT
public:
    explicit DestinationItem(QWidget *parent = 0,QDir dir = QDir(""));
    void setDir(QDir dir);

private:
    QHBoxLayout* m_qvblMainLayout;
    QVBoxLayout* m_qvblButtonLayout;
    QVBoxLayout* m_qvblTextLayout;

    QLabel* m_qlName;
    QLabel* m_qlPath;

    PushButton* m_pbEdit;
    PushButton* m_pbDel;

signals:
    void EditClickedSignal(QString name);
    void DelClickedSignal(QString name);

private slots:
    void EditClicked();
    void DelClicked();
};

#endif // DESTINATIONITEM_H
