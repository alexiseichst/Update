#ifndef LOADFILEWIDGET_H
#define LOADFILEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QDir>

#include "pushbutton.h"
#include "filelist.h"

class LoadFileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadFileWidget(QWidget *parent = 0);

private:
    QVBoxLayout* m_qvblMainLayout;

    QHBoxLayout* m_qvblPathLayout;
    QLineEdit* m_qleFolderPath;
    PushButton* m_qpbOpenFolerPath;
    PushButton* m_qlValidFolderPath;
    FileList* m_flFileList;

    QDir* m_qdCurrentFolder;
    QStringList* m_qslFileList;

    void NewFolder();
    void NewDir(QString path);


private slots:
    void OpenFolerPathClicked();
    void LineFolderPathReturn();

public slots:
};

#endif // LOADFILEWIDGET_H
