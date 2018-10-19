#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QDialog>
#include <QTextEdit>

class Console : public QDialog
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);
    QVBoxLayout* m_qvblMainLayout;
    QTextEdit* m_qteText;

signals:

public slots:
};

#endif // CONSOLE_H
