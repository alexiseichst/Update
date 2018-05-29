#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>

#include "loadfilewidget.h"
#include "destinationwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QHBoxLayout* m_qhblMainLayout;
    LoadFileWidget *m_lfwLoadFileWidget;
    DestinationWidget *m_lfwDestinationWidget;
};

#endif // MAINWINDOW_H
