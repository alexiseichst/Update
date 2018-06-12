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
    m_qlValidFolderPath->setToolTip("Error");
    m_qvblPathLayout->addWidget(m_qlValidFolderPath);
    m_qlValidFolderPath->setMinimumSize(22,22);
    m_qlValidFolderPath->setIconSize(QSize(22,22));

    m_qleFolderPath = new QLineEdit(this);
    m_qvblPathLayout->addWidget(m_qleFolderPath);
    m_qleFolderPath->setStyleSheet(" QLineEdit {border: 2px solid gray;border-radius: 5px;padding: 0 8px;}");
    m_qleFolderPath->setMinimumWidth(200);
    connect(m_qleFolderPath,SIGNAL(textChanged(QString)),this,SLOT(LineFolderPathReturnSlot()));

    m_qpbOpenFolerPath = new PushButton(this,":/Icon/folder.png");
    m_qpbOpenFolerPath->setToolTip("Open new folder");
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
    QString dir = "";

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/");

    if (dir != "")
    {
        m_qdCurrentFolder.setPath(dir);
        NewDir(dir);
    }
}

void LoadFileWidget::LineFolderPathReturnSlot()
{
    NewDir(m_qleFolderPath->text());
}

void LoadFileWidget::NewDir(QString path)
{
    QDir dir(path);

    if (dir.exists())
    {
        m_qdCurrentFolder.setPath(path);
    }

    NewFolder();
}

void LoadFileWidget::NewFolder()
{
     QStringList tmpList;
     QList<QIcon> iconList;

     m_qlValidFolderPath->setIconCustom(":/Icon/error.png");
     m_qlValidFolderPath->setToolTip("Error");
     m_flFileList->emptyList();

    if (m_qdCurrentFolder.path()==NULLDIR)
        return;

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
            m_qslFileList->append(fileName);
            iconList.append(getIconApp(fileName));
        }
    }

    m_flFileList->setList(*m_qslFileList,iconList);
    m_qlValidFolderPath->setIconCustom(":/Icon/success.png");
    m_qlValidFolderPath->setToolTip("Success");

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
        hInstance = ::GetModuleHandle(NULL);
        Icon = ::ExtractIcon(hInstance, convertedName, 0);
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

void LoadFileWidget::setStringList(QStringList list)
{
    m_flFileList->setSelected(list);
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
