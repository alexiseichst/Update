#include "loadfilewidget.h"

LoadFileWidget::LoadFileWidget(QWidget *parent) : QWidget(parent)
{
    setAcceptDrops(false);

    m_qslFileList = nullptr;
    m_qdCurrentFolder = nullptr;

    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qvblPathLayout = new QHBoxLayout(m_qvblMainLayout->widget());
    m_qvblMainLayout->addLayout(m_qvblPathLayout);

    m_qlValidFolderPath = new PushButton(this,":/Icon/error.png");
    m_qvblPathLayout->addWidget(m_qlValidFolderPath);
    m_qlValidFolderPath->setMinimumSize(22,22);
    m_qlValidFolderPath->setIconSize(QSize(22,22));

    m_qleFolderPath = new QLineEdit(this);
    m_qvblPathLayout->addWidget(m_qleFolderPath);
    m_qleFolderPath->setStyleSheet(" QLineEdit {border: 2px solid gray;border-radius: 5px;padding: 0 8px;}");
    m_qleFolderPath->setMinimumWidth(200);
    connect(m_qleFolderPath,SIGNAL(textChanged(QString)),this,SLOT(LineFolderPathReturn()));

    m_qpbOpenFolerPath = new PushButton(this,":/Icon/folder.png");
    m_qvblPathLayout->addWidget(m_qpbOpenFolerPath);
    connect(m_qpbOpenFolerPath,SIGNAL(clicked(bool)),this,SLOT(OpenFolerPathClicked()));
    m_qpbOpenFolerPath->setMinimumSize(22,22);
    m_qpbOpenFolerPath->setIconSize(QSize(22,22));

    m_flFileList = new FileList(this);
    m_qvblMainLayout->addWidget(m_flFileList);
}


void LoadFileWidget::OpenFolerPathClicked()
{
    QString dir = "";

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "/",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    if (dir != "")
    {
        if (m_qdCurrentFolder)
            delete m_qdCurrentFolder;
        m_qdCurrentFolder = new QDir(dir);
    }
    NewDir(dir);
    NewFolder();
}

void LoadFileWidget::LineFolderPathReturn()
{
    NewDir(m_qleFolderPath->text());
    NewFolder();
}

void LoadFileWidget::NewDir(QString path)
{
    QDir dir(path);

    if (m_qdCurrentFolder)
        delete m_qdCurrentFolder;
    m_qdCurrentFolder=nullptr;

    if (dir.exists())
    {
        m_qdCurrentFolder = new QDir(dir);
    }

    NewFolder();
}

void LoadFileWidget::NewFolder()
{
    QStringList listTmp;

     m_qlValidFolderPath->setIconCustom(":/Icon/error.png");
     m_flFileList->emptyList();

    if (!m_qdCurrentFolder)
        return;

    m_qleFolderPath->setText(m_qdCurrentFolder->path());

    listTmp = QStringList(m_qdCurrentFolder->entryList(QStringList() << "*.exe" << "*.dll",QDir::Files));

    if (m_qslFileList)
        delete m_qslFileList;
    m_qslFileList = new QStringList();

    if (listTmp.size()<1)
        return;

    for(int iList=0;iList<listTmp.size();iList++)
    {
        QString tmp = listTmp.at(iList);
        if(tmp.at(tmp.size()-1)=='e')
        {
            m_qslFileList->insert(0,tmp);
        }
        else
        {
            m_qslFileList->append(tmp);
        }

    }

    m_flFileList->setList(*m_qslFileList);
    m_qlValidFolderPath->setIconCustom(":/Icon/success.png");

}
