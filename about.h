#ifndef ABOUT_H
#define ABOUT_H

#include <QObject>
#include <QDialog>
#include <QLineEdit>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include <QFileDialog>
#include <QVersionNumber>

#include "pushbutton.h"
#include "define.h"

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0);

private:
    QVBoxLayout* m_qvblMainLayout;

    QLabel* m_qlVersion;
    QVersionNumber m_qvnVersion;
    PushButton* m_pbLogo;

private slots:

};

#endif // ABOUT_H
