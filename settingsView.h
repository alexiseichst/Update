#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

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

class SettingsView : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsView(QWidget *parent = 0);

private:
    QVBoxLayout* m_qvblMainLayout;

private slots:

};

#endif // SETTINGSVIEW_H
