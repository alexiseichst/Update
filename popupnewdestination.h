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
#include <QCheckBox>

#include "pushbutton.h"
#include "define.h"

#define LEFT 10
#define TOP 10
#define SPACE 10



class PopUpNewDestination : public QDialog
{
    Q_OBJECT
public:
    explicit PopUpNewDestination(QWidget *parent = 0,QDir dir=QDir(NULLDIR),QDir lastDir=QDir(NULLDIR),bool createCopy=false,bool newDest=true);
    QDir getQDir();
    bool getCreateCopy();

private:
    QVBoxLayout* m_qvblMainLayout;
    QLabel* m_qlName;
    QHBoxLayout* m_qvblPathLayout;
    PushButton* m_qlValidFolderPath;
    QLineEdit* m_qleFolderPath;
    PushButton* m_qpbOpenFolerPath;
    QCheckBox* m_qcbCreateCopy;
    QDialogButtonBox* mqdbButtons;
    QDir m_qdCurrentFolder;
    QDir m_qdLastFolder;
    bool m_bNew;

    void NewFolder(bool setText=false);
    void NewDir(QString path);

private slots:
    void OpenFolerPathClickedSlot();
    void LineFolderPathChangeSlot();
    void DialogBoxButtonSlot(QAbstractButton* button);
    void ExitSlot(bool ok=false);
};

#endif // POPUPNEWDESTINATION_H
