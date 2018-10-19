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
     bool firstDll=true;

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

    if (m_qslFileList)
        delete m_qslFileList;
    m_qslFileList = new QStringList();

    if (tmpList.size()<1)
        return;

    for(int iList=0;iList<tmpList.size();iList++)
    {
        QString fileName = tmpList.at(iList);
        if(fileName.mid(fileName.size()-3,3)=="exe")
        {
            m_qslFileList->insert(0,fileName);
            iconList.insert(0,getIconApp(fileName));
        }
        else
        {
            if (firstDll)
            {
                m_qslFileList->append("Toutes les dll");
                iconList.append(QIcon(":/Icon/star.png"));
                firstDll=false;
            }
            m_qslFileList->append(fileName);
            iconList.append(getIconApp(fileName));
        }
    }

    m_flFileList->setList(*m_qslFileList,iconList);
    m_qlValidFolderPath->setIconCustom(":/Icon/success.png");
    m_qlValidFolderPath->setToolTip("Valide");

}

QIcon LoadFileWidget::getIconApp(QString fileName)
{
    QString filePath;
    QPixmap pixmap;
    HICON Icon;
    HINSTANCE hInstance;
    wchar_t *convertedName=nullptr;
    QIcon returnedIcon;

    if(fileName.mid(fileName.size()-3,3)=="exe")
    {
        filePath = m_qdCurrentFolder.path()+"/"+fileName;
        convertedName = new wchar_t[filePath.length() + 1];
        filePath.toWCharArray(convertedName);
        convertedName[filePath.length()] = '\0';
        hInstance = ::GetModuleHandle(LPCWSTR("Kernel32.dll"));
        Icon = ::ExtractIcon(hInstance, convertedName, 0);

        if (Icon)
            pixmap = QtWin::fromHICON(Icon);

        if (pixmap.isNull())
            returnedIcon = QIcon(":/Icon/exe.png");
        else
            returnedIcon = QIcon(pixmap);

    }
    else
    {
        returnedIcon = QIcon(":/Icon/dll.png");
    }

    delete convertedName;
    return returnedIcon;
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
