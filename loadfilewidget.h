#ifndef LOADFILEWIDGET_H
#define LOADFILEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QDir>
#include <QtWin>

#include "pushbutton.h"
#include "filelist.h"
#include "define.h"

class LoadFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadFileWidget(QWidget *parent = 0,QString filesDir="");
    void setStringList(QStringList list,bool allExe=false,bool allDll=false);
    void sendSelectedFiles();
    QDir getDir();
    QStringList getFilesList();

private:
    QVBoxLayout* m_qvblMainLayout;
    QHBoxLayout* m_qvblPathLayout;
    QLineEdit* m_qleFolderPath;
    PushButton* m_qpbOpenFolerPath;
    PushButton* m_qlValidFolderPath;
    FileList* m_flFileList;
    QDir m_qdCurrentFolder;
    QStringList* m_qslFileList;
    QString m_qsLastPath;

    void NewFolder();
    void NewDir(QString path);
    QIcon getIconApp(QString path);

private slots:
    void OpenFolerPathClickedSlot();
    void LineFolderPathReturnSlot();
    void sendSelectedFilesSlotSlot(QStringList);
    void newFilesListSlot();

signals:
    void sendSelectedFilesSlotSignal(QStringList);
    void newFilesListSignal();
};

#endif // LOADFILEWIDGET_H
