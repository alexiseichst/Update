#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QList>
#include <QString>
#include <QTimer>
#include <QKeyEvent>

#include "loadfilewidget.h"
#include "destinationwidget.h"
#include "settings.h"
#include "pushbutton.h"
#include "copyfiles.h"
#include "define.h"
#include "about.h"
#include "preferences.h"
#include "missingfiles.h"
#include "console.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setStructList(QList<COPYSTRUCT> list);
    void setFilesDir(QDir dir);

private:
    Ui::MainWindow *ui;
    QVBoxLayout* m_qhblAppLayout;
    QHBoxLayout* m_qhblMainLayout;
    LoadFileWidget *m_lfwLoadFileWidget;
    DestinationWidget *m_lfwDestinationWidget;
    QList<COPYSTRUCT*> *m_qlCopyList;
    COPYSTRUCT* m_cpCurrentCopyStruct;
    CopyFiles* m_cfCopyFiles;
    QVBoxLayout* m_qhblCenterLayout;
    PushButton* m_pbPlayButton;
    PushButton* m_pbAboutButton;
    PushButton* m_pbPreferenceButton;
    PushButton* m_pbWarningButton;
    QTimer* m_qtWarningTimer;
    QList<PREFSTRUCT*> *m_qlPrefList;

    void updateSelectedFiles();
    void validPlay();
    void missingFile(bool openWindow=false);
    bool preferences(QDir dir);
    void saveConf();

private slots:
    void destinationListChange(QList<DESTSELECT> list);
    void newSelectedFilesSlot(QStringList list);
    void playSlot();
    void preferenceSlot();
    void newFilesListSlot();
    void aboutSlot();
    void warningSlot();
    void warningTimerSlot();
};

#endif // MAINWINDOW_H
