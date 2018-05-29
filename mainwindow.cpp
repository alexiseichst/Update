#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPixmap pixmap(":/Icon/server.png");
    QIcon ButtonIcon(pixmap);

    ui->setupUi(this);
    ui->centralWidget->setAcceptDrops(true);

    setWindowTitle("Update");
    setWindowIcon(ButtonIcon);

    m_qhblMainLayout = new QHBoxLayout(ui->centralWidget);

    m_lfwLoadFileWidget = new LoadFileWidget(this);
    m_qhblMainLayout->addWidget(m_lfwLoadFileWidget);

    m_lfwDestinationWidget = new DestinationWidget(this);
    m_qhblMainLayout->addWidget(m_lfwDestinationWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
