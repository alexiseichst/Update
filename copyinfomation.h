#ifndef COPYINFOMATION_H
#define COPYINFOMATION_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

class CopyInfomation : public QDialog
{
    Q_OBJECT
public:
    explicit CopyInfomation(QWidget *parent = 0,QString result="");

private:
    QString m_qsResult;

    QVBoxLayout* m_qvblMainLayout;

    QLabel* m_qlTitle;
    QTextEdit* m_qteDetail;

    QHBoxLayout* m_qhblButtonsLayout;
    QPushButton* m_qpbExit;

    void boldSrcDest();

signals:
};

#endif // COPYINFOMATION_H
