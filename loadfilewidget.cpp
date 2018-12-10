#include "loadfilewidget.h"

LoadFileWidget::LoadFileWidget(QWidget *parent,QString filesDir) : QWidget(parent)
{     
    setAcceptDrops(false);

    m_qslFileList = nullptr;
    m_qdCurrentFolder = nullptr;

    m_qvblMainLayout = new QVBoxLayout(this);
    this->setLayout(m_qvblMainLayout);

    m_qvblPathLayout = new QHBoxLayout(m_qvblMainLayout->widget());
    m_qvblMainLayout->addLayout(m_qvblPathLayout);

    m_qlValidFolderPath = new PushButton(this,":/Icon/error.png",false);
    m_qlValidFolderPath->setToolTip("Erreur");
    m_qvblPathLayout->addWidget(m_qlValidFolderPath);
    m_qlValidFolderPath->setMinimumSize(22,22);
    m_qlValidFolderPath->setIconSize(QSize(22,22));

    m_qleFolderPath = new QLineEdit(this);
    m_qvblPathLayout->addWidget(m_qleFolderPath);
    m_qleFolderPath->setStyleSheet(" QLineEdit {border: 2px solid gray;border-radius: 5px;padding: 0 8px;}");
    m_qleFolderPath->setMinimumWidth(200);
    connect(m_qleFolderPath,SIGNAL(textChanged(QString)),this,SLOT(LineFolderPathReturnSlot()));

    m_qpbOpenFolerPath = new PushButton(this,":/Icon/folder.png");
    m_qpbOpenFolerPath->setToolTip("Ouvrir un nouveau dossier");
    m_qvblPathLayout->addWidget(m_qpbOpenFolerPath);
    connect(m_qpbOpenFolerPath,SIGNAL(clicked(bool)),this,SLOT(OpenFolerPathClickedSlot()));
    m_qpbOpenFolerPath->setMinimumSize(22,22);
    m_qpbOpenFolerPath->setIconSize(QSize(22,22));

    m_flFileList = new FileList(this);
    m_qvblMainLayout->addWidget(m_flFileList);
    connect(m_flFileList,SIGNAL(sendSelectedFilesSlotSignal(QStringList)),this,SLOT(sendSelectedFilesSlotSlot(QStringList)));
    connect(m_flFileList,SIGNAL(newFileListSignal()),this,SLOT(newFilesListSlot()));

    if (filesDir!=NULLDIR)
        NewDir(filesDir);
}


void LoadFileWidget::OpenFolerPathClickedSlot()
{
    QDir dir(m_qdCurrentFolder);
    QString path="/";

    if (pingPc(dir) && dir.exists())
    {
        dir.cdUp();
        if (dir.exists())
        {
            path = dir.path();
        }
    }

    path = QFileDialog::getExistingDirectory(this, tr("Ouvrir un dossier"),path);
    m_qsLastPath=path;

    if (path != "")
    {
        m_qdCurrentFolder.setPath(path);
        NewDir(path);
    }
}

void LoadFileWidget::LineFolderPathReturnSlot()
{
    NewDir(m_qleFolderPath->text());
}

void LoadFileWidget::NewDir(QString path)
{
    QDir dir(path);

    if (pingPc(dir) && dir.exists())
    {
        m_qdCurrentFolder.setPath(path);
    }
    else
    {
        m_qdCurrentFolder.setPath(NULLDIR);
    }
    NewFolder();
}

void LoadFileWidget::NewFolder()
{
     QStringList tmpList;
     QList<QIcon> iconList;
     QFileInfoList infoList;

     m_qlValidFolderPath->setIconCustom(":/Icon/error.png");
     m_qlValidFolderPath->setToolTip("Erreur");
     m_flFileList->emptyList();

    if (m_qdCurrentFolder.path()==NULLDIR || !pingPc(m_qdCurrentFolder) || !m_qdCurrentFolder.exists())
        return;

    addLog("Nouveau repertoire de fichiers source : "+m_qdCurrentFolder.path());

    disconnect(m_qleFolderPath,SIGNAL(textChanged(QString)),this,SLOT(LineFolderPathReturnSlot()));
    m_qleFolderPath->setText(m_qdCurrentFolder.path());
    connect(m_qleFolderPath,SIGNAL(textChanged(QString)),this,SLOT(LineFolderPathReturnSlot()));

    tmpList = QStringList(m_qdCurrentFolder.entryList(QStringList() << "*.exe" << "*.dll",QDir::Files));
    infoList = m_qdCurrentFolder.entryInfoList();

    if (m_qslFileList)
        delete m_qslFileList;
    m_qslFileList = new QStringList();

    if (tmpList.size()<1)
        return;

    for(int iList=0;iList<tmpList.size();iList++)
    {
        for(int iInfoList=0;iInfoList<infoList.size();iInfoList++)
        {
            if (tmpList.at(iList)==infoList.at(iInfoList).fileName())
            {
                QString name = tmpList.at(iList);
                if (name.at(name.size()-3)=='e' &&
                    name.at(name.size()-2)=='x' &&
                    name.at(name.size()-1)=='e')
                {
                    FileIconProvider iconProv;
                    iconList.insert(0,iconProv.icon(infoList.at(iInfoList)));
                    infoList.removeAt(iInfoList);
                    m_qslFileList->insert(0,name);
                    break;
                }

                if (name.at(name.size()-3)=='d' &&
                    name.at(name.size()-2)=='l' &&
                    name.at(name.size()-1)=='l')
                {
                    FileIconProvider iconProv;
                    iconList.append(iconProv.icon(infoList.at(iInfoList)));
                    infoList.removeAt(iInfoList);
                    m_qslFileList->append(name);
                    break;
                }
            }
        }
    }

    for(int iFileList=0;iFileList<m_qslFileList->size();iFileList++)
    {
        QString name = m_qslFileList->at(iFileList);
        if (name.at(name.size()-3)=='d' &&
            name.at(name.size()-2)=='l' &&
            name.at(name.size()-1)=='l')
        {
            m_qslFileList->insert(iFileList,ALLDLLNAME);
            iconList.insert(iFileList,QIcon(":/Icon/star.png"));
            break;
        }
    }
    m_flFileList->setList(*m_qslFileList,iconList);
    m_qlValidFolderPath->setIconCustom(":/Icon/success.png");
    m_qlValidFolderPath->setToolTip("Valide");

}

void LoadFileWidget::setStringList(QStringList list,bool allExe,bool allDll)
{
    m_flFileList->setSelected(list,allExe,allDll);
}

void LoadFileWidget::sendSelectedFiles()
{
    m_flFileList->sendSelectedFiles();
}

void LoadFileWidget::sendSelectedFilesSlotSlot(QStringList list)
{
    emit sendSelectedFilesSlotSignal(list);
}

QDir LoadFileWidget::getDir()
{
    return m_qdCurrentFolder;
}

void LoadFileWidget::newFilesListSlot()
{
    emit newFilesListSignal();
}

QStringList LoadFileWidget::getFilesList()
{
    return m_flFileList->getFilesList();
}
