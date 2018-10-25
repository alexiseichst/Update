#ifndef DESTINATIONITEM_H
#define DESTINATIONITEM_H

#include <QObject>
#include <QWidget>
#include <QDir>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "pushbutton.h"
#include "define.h"

class DestinationItem : public QWidget
{
    Q_OBJECT
public:
    explicit DestinationItem(QWidget *parent = 0,QDir dir = QDir(NULLDIR),bool createCopy=false);
    void setDir(QDir dir);
    QDir getDir();
    bool getCreateCopy();
    void setCreateCopy(bool createCopy);
    void setCopyOk(bool state);

private:
    QHBoxLayout* m_qvblMainLayout;
    QVBoxLayout* m_qvblButtonLayout;
    QHBoxLayout* m_qvblTextTopLayout;
    QVBoxLayout* m_qvblTextLayout;
    QLabel* m_qlName;
    QLabel* m_qlPath;
    bool m_bCreateCopy;
    PushButton* m_pbEdit;
    PushButton* m_pbDel;
    QDir m_qdDir;

signals:
    void EditClickedSignal(QString name);
    void DelClickedSignal(QString name);

private slots:
    void EditClicked();
    void DelClicked();
};

#endif // DESTINATIONITEM_H
