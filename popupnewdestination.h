#ifndef POPUPNEWDESTINATION_H
#define POPUPNEWDESTINATION_H

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

#include "pushbutton.h"

#define LEFT 10
#define TOP 10
#define SPACE 10



class PopUpNewDestination : public QDialog
{
    Q_OBJECT
public:
    explicit PopUpNewDestination(QWidget *parent = 0);

    QDir* getQDir();

private:
    QVBoxLayout* m_qvblMainLayout;

    QLabel* m_qlName;

    QHBoxLayout* m_qvblPathLayout;
    PushButton* m_qlValidFolderPath;
    QLineEdit* m_qleFolderPath;
    PushButton* m_qpbOpenFolerPath;

    QDialogButtonBox* mqdbButtons;

    QDir* m_qdCurrentFolder;

    void NewFolder();
    void NewDir(QString path);

signals:

private slots:
    void OpenFolerPathClicked();
    void LineFolderPathReturn();
    void acceptButton();
    void rejectedButton();
};

#endif // POPUPNEWDESTINATION_H
