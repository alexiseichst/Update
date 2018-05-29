#include "popupnewdestination.h"

PopUpNewDestination::PopUpNewDestination(QWidget *parent) : QDialog(parent)
{   
    QFont font;
    QPalette pal = palette();

    m_qdCurrentFolder = nullptr;

    setMaximumSize(300,200);
    setMinimumSize(300,200);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qlName  = new QLabel(this);
    m_qlName->setMinimumHeight(100);
    m_qvblMainLayout->addWidget(m_qlName);
    m_qlName->setAlignment(Qt::AlignCenter);
    m_qlName->setText("Name");
    font = m_qlName->font();
    font.setPointSize(30);
    font.setBold(true);
    m_qlName->setFont(font);

    m_qvblPathLayout = new QHBoxLayout(m_qvblMainLayout->widget());
    m_qvblMainLayout->addLayout(m_qvblPathLayout);

    m_qlValidFolderPath = new PushButton(this,":/Icon/error.png");
    m_qlValidFolderPath->setMinimumSize(22,22);
    m_qlValidFolderPath->setIconSize(QSize(22,22));
    m_qvblPathLayout->addWidget(m_qlValidFolderPath);

    m_qleFolderPath = new QLineEdit(this);
    m_qleFolderPath->setStyleSheet(" QLineEdit {border: 2px solid gray;border-radius: 5px;padding: 0 8px;}");
    m_qleFolderPath->setMinimumWidth(200);
    m_qvblPathLayout->addWidget(m_qleFolderPath);
    connect(m_qleFolderPath,SIGNAL(textChanged(QString)),this,SLOT(LineFolderPathReturn()));

    m_qpbOpenFolerPath = new PushButton(this,":/Icon/folder.png");
    connect(m_qpbOpenFolerPath,SIGNAL(clicked(bool)),this,SLOT(OpenFolerPathClicked()));
    m_qpbOpenFolerPath->setMinimumSize(22,22);
    m_qpbOpenFolerPath->setIconSize(QSize(22,22));
    m_qvblPathLayout->addWidget(m_qpbOpenFolerPath);

    mqdbButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,this);
    m_qvblMainLayout->addWidget(new QLabel(this));
    m_qvblMainLayout->addWidget(mqdbButtons);
    connect(mqdbButtons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(mqdbButtons, SIGNAL(rejected()), this, SLOT(reject()));

    show();
}

void PopUpNewDestination::OpenFolerPathClicked()
{
    QString dir = "";

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "/",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    NewDir(dir);
    NewFolder();
}

void PopUpNewDestination::NewDir(QString path)
{
    QDir dir(path);

    if (m_qdCurrentFolder)
        delete m_qdCurrentFolder;
    m_qdCurrentFolder=nullptr;

    if (dir.exists())
    {
        m_qdCurrentFolder = new QDir(dir);
    }
}
void PopUpNewDestination::LineFolderPathReturn()
{
     NewDir(m_qleFolderPath->text());
     NewFolder();
}

void PopUpNewDestination::NewFolder()
{

     m_qlValidFolderPath->setIconCustom(":/Icon/error.png");

    if (!m_qdCurrentFolder)
        return;

    m_qleFolderPath->setText(m_qdCurrentFolder->path());
    m_qlName->setText(m_qdCurrentFolder->dirName());
    m_qlValidFolderPath->setIconCustom(":/Icon/success.png");

}

void PopUpNewDestination::acceptButton()
{
    close();
}

void PopUpNewDestination::rejectedButton()
{
    if (m_qdCurrentFolder)
        delete m_qdCurrentFolder;
    m_qdCurrentFolder = nullptr;

    close();
}

QDir* PopUpNewDestination::getQDir()
{
    if(m_qdCurrentFolder)
        return new QDir(*m_qdCurrentFolder);
    else
        return nullptr;
}

