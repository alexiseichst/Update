#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPixmap pixmap(":/Icon/server.png");
    QIcon ButtonIcon(pixmap);
    Settings settings;
    QRect windowsRect;
    QList<DESTSELECT> list;
    QString fileFolder = NULLDIR;

    addLog("");
    addLog("Lancement de l'application");

    m_qlPrefList = new QList<PREFSTRUCT*>;
    Preferences pref(m_qlPrefList,this,true);

    m_cpCurrentCopyStruct = nullptr;
    m_cfCopyFiles = nullptr;

    m_qlCopyList = new QList<COPYSTRUCT*>;
    settings.load(&windowsRect,m_qlCopyList,&fileFolder);

    ui->setupUi(this);

    setWindowTitle("Update");
    setWindowIcon(ButtonIcon);

    m_qhblAppLayout = new QVBoxLayout(ui->centralWidget);

    m_qhblMainLayout = new QHBoxLayout();
    m_qhblAppLayout->addLayout(m_qhblMainLayout);

    m_lfwLoadFileWidget = new LoadFileWidget(this,fileFolder);
    m_qhblMainLayout->addWidget(m_lfwLoadFileWidget);
    connect(m_lfwLoadFileWidget,SIGNAL(sendSelectedFilesSlotSignal(QStringList)),SLOT(newSelectedFilesSlot(QStringList)));
    connect(m_lfwLoadFileWidget,SIGNAL(newFilesListSignal()),this,SLOT(newFilesListSlot()));

    m_qhblCenterLayout= new QVBoxLayout();
    m_qhblCenterLayout->setAlignment(Qt::AlignCenter);
    m_qhblMainLayout->addLayout(m_qhblCenterLayout);

    m_pbPlayButton = new PushButton(this,":/Icon/play.png");
    m_pbPlayButton->setToolTip("Commencer la copie");
    m_pbPlayButton->setMinimumSize(30,30);
    m_pbPlayButton->setIconSize(QSize(30,30));
    m_qhblCenterLayout->addWidget(m_pbPlayButton);
    m_pbPlayButton->setDisabled(true);
    connect(m_pbPlayButton,SIGNAL(clicked(bool)),SLOT(playSlot()));

    m_qhblCenterLayout->setSpacing(50);

    m_pbPreferenceButton = new PushButton(this,":/Icon/compose.png");
    m_pbPreferenceButton->setToolTip("Selection automatique");
    m_pbPreferenceButton->setMinimumSize(30,30);
    m_pbPreferenceButton->setIconSize(QSize(30,30));
    m_qhblCenterLayout->addWidget(m_pbPreferenceButton);
    connect(m_pbPreferenceButton,SIGNAL(clicked(bool)),SLOT(preferenceSlot()));

    m_qhblCenterLayout->setSpacing(50);

    m_pbAboutButton =  new PushButton(this,":/Icon/info.png");
    m_pbAboutButton->setToolTip("A propos");
    m_pbAboutButton->setMinimumSize(30,30);
    m_pbAboutButton->setIconSize(QSize(30,30));
    connect(m_pbAboutButton,SIGNAL(clicked(bool)),SLOT(aboutSlot()));
    m_qhblCenterLayout->addWidget(m_pbAboutButton);

    m_pbWarningButton =  new PushButton(this,":/Icon/warning.png");
    m_pbWarningButton->setToolTip("Fichiers manquants");
    m_pbWarningButton->setMinimumSize(30,30);
    m_pbWarningButton->setIconSize(QSize(30,30));
    m_pbWarningButton->hide();
    connect(m_pbWarningButton,SIGNAL(clicked(bool)),SLOT(warningSlot()));
    m_qhblCenterLayout->addWidget(m_pbWarningButton);
    m_qtWarningTimer = new QTimer(m_pbWarningButton);
    connect(m_qtWarningTimer,SIGNAL(timeout()),SLOT(warningTimerSlot()));

    for (int iList=0;iList<m_qlCopyList->size();iList++)
    {
        DESTSELECT struc;
        struc.dir = m_qlCopyList->at(iList)->Destdir;
        struc.id = m_qlCopyList->at(iList)->Id;
        struc.createCopy = m_qlCopyList->at(iList)->createCopy;
        struc.selected = false;
        list.append(struc);
    }
    m_lfwDestinationWidget = new DestinationWidget(this,list);
    m_qhblMainLayout->addWidget(m_lfwDestinationWidget);
    connect(m_lfwDestinationWidget,SIGNAL(selectedListSignal(QList<DESTSELECT>)),SLOT(destinationListChange(QList<DESTSELECT>)));
    m_lfwDestinationWidget->selectedChange();

    setGeometry(windowsRect);
    missingFile(false);

    addLog("Fin du chargement");
}

MainWindow::~MainWindow()
{
    saveConf();
    delete m_qlCopyList;
    delete ui;
    addLog("Fermeture de l'application");
}

void MainWindow::saveConf()
{
    Settings settings;
    QRect rectArg = geometry();
    settings.save(&rectArg,m_qlCopyList,m_lfwLoadFileWidget->getDir().path());
}

void MainWindow::destinationListChange(QList<DESTSELECT> list)
{
    int selected = -1;
    COPYSTRUCT* ptCopyStruct=nullptr;
    bool inList=false;
    bool update=true;

    m_cpCurrentCopyStruct = nullptr;

    for (int iListArg=0;iListArg<list.size();iListArg++)
    {
        selected = -1;
        for (int iList=0;iList<m_qlCopyList->size();iList++)
        {
            if (m_qlCopyList->at(iList)->Id == list.at(iListArg).id) // Le dir de destination selectionné existe déja
            {
                selected=iList;
                break;
            }
        }
        if (selected<0) // Ajout nouveau
        {
            m_qlCopyList->append(new COPYSTRUCT);
            ptCopyStruct = m_qlCopyList->last();
            ptCopyStruct->Id = list.at(iListArg).id;
            update = preferences(list.at(iListArg).dir);
        }
        else // Mise à jour
        {
            ptCopyStruct = m_qlCopyList->at(selected);           
        }
        ptCopyStruct->Destdir = list.at(iListArg).dir;
        ptCopyStruct->createCopy = list.at(iListArg).createCopy;

        if (list.at(iListArg).selected) // Pointeur sur le nouveau courant
            m_cpCurrentCopyStruct = ptCopyStruct;
    }

    for (int iList=0;iList<m_qlCopyList->size();iList++)
    {
        inList=false;
        for (int iListArg=0;iListArg<list.size();iListArg++)
        {
            if (m_qlCopyList->at(iList)->Id == list.at(iListArg).id) // Le dir de destination existe toujours
            {
                inList=true;
                break;
            }
        }
        if (!inList)
        {
            delete m_qlCopyList->at(iList);
            m_qlCopyList->removeAt(iList);
        }
    }
    if (update)
    {
        updateSelectedFiles();
    }
    else
    {
        m_lfwLoadFileWidget->sendSelectedFiles();
    }
    validPlay();
}

bool MainWindow::preferences(QDir dir)
{
    for (int iStruct=0;iStruct<m_qlPrefList->size();iStruct++)
    {
        for (int iNames=0;iNames<m_qlPrefList->at(iStruct)->names.size();iNames++)
        {
            if (!QString::compare(dir.dirName(),m_qlPrefList->at(iStruct)->names.at(iNames),Qt::CaseInsensitive))
            {
                m_lfwLoadFileWidget->setStringList(m_qlPrefList->at(iStruct)->files,m_qlPrefList->at(iStruct)->allExe,m_qlPrefList->at(iStruct)->allDll);
                return false;
            }
        }
    }
    return true;
}

void MainWindow::updateSelectedFiles()
{
    if (m_cpCurrentCopyStruct)
    {
        m_lfwLoadFileWidget->setStringList(m_cpCurrentCopyStruct->FileList);
    }
    else
    {
        m_lfwLoadFileWidget->setStringList(QStringList());
    }
}

void MainWindow::newSelectedFilesSlot(QStringList list)
{
    bool add=false;
    bool inList=false;
    bool bsaveConf=false;

    if (m_cpCurrentCopyStruct)
    {
        for (int iListArg=0;iListArg<list.size();iListArg++)
        {
            add = true;
            for (int iList=0;iList<m_cpCurrentCopyStruct->FileList.size();iList++)
            {
                if (m_cpCurrentCopyStruct->FileList.at(iList) == list.at(iListArg))
                {
                    add = false;
                    break;
                }
            }
            if (add)
            {
                bsaveConf=true;
                m_cpCurrentCopyStruct->FileList.append(list.at(iListArg));
            }
        }
        for (int iList=0;iList<m_cpCurrentCopyStruct->FileList.size();iList++)
        {
            inList=false;
            for (int iListArg=0;iListArg<list.size();iListArg++)
            {
                if (m_cpCurrentCopyStruct->FileList.at(iList) == list.at(iListArg))
                {
                    inList=true;
                    break;
                }
            }
            if (!inList)
            {
                m_cpCurrentCopyStruct->FileList.removeAt(iList);
                bsaveConf=true;
            }
        }
    }
    if (bsaveConf)
    {
        saveConf();
    }
    validPlay();
}

void MainWindow::playSlot()
{
    Settings settings;
    QRect rectArg = geometry();
    static bool info=false;
    settings.save(&rectArg,m_qlCopyList,m_lfwLoadFileWidget->getDir().path());

    if (m_cfCopyFiles)
        delete m_cfCopyFiles;
    m_cfCopyFiles = new CopyFiles(this,info);

    m_cfCopyFiles->setFilesDir(m_lfwLoadFileWidget->getDir());
    m_cfCopyFiles->setStructList(m_qlCopyList);
    QCoreApplication::processEvents();
    m_cfCopyFiles->startCopySlot(true,true);
    m_cfCopyFiles->exec();
    info = m_cfCopyFiles->getInfo();

}

void MainWindow::validPlay()
{
    m_pbPlayButton->setDisabled(true);
    for (int iList=0;iList<m_qlCopyList->size();iList++)
    {
        if (m_qlCopyList->at(iList)->FileList.size()>0)
        {
            m_pbPlayButton->setDisabled(false);
            break;
        }
    }
}

void MainWindow::newFilesListSlot()
{
    updateSelectedFiles();
    missingFile(false);
}

void MainWindow::aboutSlot()
{
    About* about = nullptr;

    about = new About(this);
    about->exec();

    delete about;
}

void MainWindow::preferenceSlot()
{
    Preferences* pref = nullptr;

    pref = new Preferences(m_qlPrefList,this);
    pref->exec();

    delete pref;
}

void MainWindow::missingFile(bool openWindow)
{
    QStringList filesList;
    QList<QStringList> missingfiles;
    QList<QDir> destDirMissingfiles;
    QList<QStringList> deletefiles;
    QStringList tmpList;
    bool valid=false;

    filesList = m_lfwLoadFileWidget->getFilesList();

    for (int iStruct=0;iStruct<m_qlCopyList->size();iStruct++)
    {
        tmpList.clear();
        for (int iFileDest=0;iFileDest<m_qlCopyList->at(iStruct)->FileList.size();iFileDest++)
        {
            valid=false;
            for (int iFile=0;iFile<filesList.size();iFile++)
            {
                if (m_qlCopyList->at(iStruct)->FileList.at(iFileDest)==filesList.at(iFile))
                {
                    valid=true;
                    break;
                }
            }
            if (!valid)
            {
                tmpList.append(m_qlCopyList->at(iStruct)->FileList.at(iFileDest));
            }
        }
        if (!tmpList.isEmpty())
        {
            destDirMissingfiles.append(m_qlCopyList->at(iStruct)->Destdir);
            missingfiles.append(QStringList(tmpList));
        }

    }
    if (!missingfiles.isEmpty())
    {
        m_pbWarningButton->show();
        m_qtWarningTimer->start(500);
        if (openWindow)
        {
            missingFiles *missingFilesDialog = new missingFiles(this,missingfiles,destDirMissingfiles);
            missingFilesDialog->exec();
            deletefiles = missingFilesDialog->getDeleteFiles();
            for (int iDir=0;iDir<destDirMissingfiles.size();iDir++)
            {
                for (int iStruct=0;iStruct<m_qlCopyList->size();iStruct++)
                {
                    if (m_qlCopyList->at(iStruct)->Destdir.path()==destDirMissingfiles.at(iDir).path())
                    {
                        for (int iFile=0;iFile<m_qlCopyList->at(iStruct)->FileList.size();iFile++)
                        {
                            for (int iDelFile=0;iDelFile<deletefiles.at(iDir).size();iDelFile++)
                            {
                                if (deletefiles.at(iDir).at(iDelFile)==m_qlCopyList->at(iStruct)->FileList.at(iFile))
                                {
                                    tmpList = m_qlCopyList->at(iStruct)->FileList;
                                    tmpList.removeAt(iFile);
                                    m_qlCopyList->at(iStruct)->FileList = tmpList;
                                }
                            }
                        }
                    }
                }
            }
            delete missingFilesDialog;

            missingFile(false);
        }
    }
    else
    {
         m_qtWarningTimer->stop();
         m_pbWarningButton->hide();
    }
}

void MainWindow::warningSlot()
{
    missingFile(true);
}

void MainWindow::warningTimerSlot()
{
    static bool iconRed=false;

    if (iconRed)
    {
        m_pbWarningButton->setIconCustom(":/Icon/warning.png");
    }
    else
    {
        m_pbWarningButton->setIconCustom(":/Icon/warningRed.png");
    }
    iconRed=!iconRed;
}
