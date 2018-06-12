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

    m_cpCurrentCopyStruct = nullptr;
    m_cfCopyFiles = nullptr;

    m_qlCopyList = new QList<COPYSTRUCT*>;
    settings.load(&windowsRect,m_qlCopyList,&fileFolder);

    ui->setupUi(this);

    setWindowTitle("Update");
    setWindowIcon(ButtonIcon);

    m_qhblAppLayout = new QVBoxLayout(ui->centralWidget);

    m_qhblMainLayout = new QHBoxLayout(this);
    m_qhblAppLayout->addLayout(m_qhblMainLayout);

    m_lfwLoadFileWidget = new LoadFileWidget(this,fileFolder);
    m_qhblMainLayout->addWidget(m_lfwLoadFileWidget);
    connect(m_lfwLoadFileWidget,SIGNAL(sendSelectedFilesSlotSignal(QStringList)),SLOT(newSelectedFilesSlot(QStringList)));
    connect(m_lfwLoadFileWidget,SIGNAL(newFilesListSignal()),this,SLOT(newFilesListSlot()));

    m_pbPlayButton = new PushButton(this,":/Icon/play.png");
    m_pbPlayButton->setToolTip("Start copy");
    m_pbPlayButton->setMinimumSize(30,30);
    m_pbPlayButton->setIconSize(QSize(30,30));
    m_qhblMainLayout->addWidget(m_pbPlayButton);
    m_pbPlayButton->setDisabled(true);
    connect(m_pbPlayButton,SIGNAL(clicked(bool)),SLOT(OnPlayButtonClicked()));

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

    m_qhblBottomLayout= new QHBoxLayout(this);
    m_qhblBottomLayout->setAlignment(Qt::AlignRight);
    m_qhblAppLayout->addLayout(m_qhblBottomLayout);

    m_pbAboutButton =  new PushButton(this,":/Icon/info.png");
    m_pbAboutButton->setMinimumSize(20,20);
    m_pbAboutButton->setIconSize(QSize(20,20));
    connect(m_pbAboutButton,SIGNAL(clicked(bool)),SLOT(aboutSlot()));
    m_qhblBottomLayout->addWidget(m_pbAboutButton);

    setGeometry(windowsRect);

}

MainWindow::~MainWindow()
{
    Settings settings;
    QRect rectArg = geometry();
    settings.save(&rectArg,m_qlCopyList,m_lfwLoadFileWidget->getDir().path());
    delete m_qlCopyList;
    delete ui;
}

void MainWindow::destinationListChange(QList<DESTSELECT> list)
{
    int selected = -1;
    COPYSTRUCT* ptCopyStruct=nullptr;
    bool inList=false;

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
    updateSelectedFiles();
    validPlay();
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
    if (m_cpCurrentCopyStruct)
    {
        for (int iListArg=0;iListArg<list.size();iListArg++)
        {
            add = true;
            for (int iList=0;iList<m_cpCurrentCopyStruct->FileList.size();iList++)
            {
                if (m_cpCurrentCopyStruct->FileList.at(iList) == list.at(iListArg)) // Le dir de destination selectionné existe déja
                {
                    add = false;
                    break;
                }
            }
            if (add)
                m_cpCurrentCopyStruct->FileList.append(list.at(iListArg));
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
                m_cpCurrentCopyStruct->FileList.removeAt(iList);
        }
    }
    validPlay();
}

void MainWindow::OnPlayButtonClicked()
{
    if (m_cfCopyFiles)
        delete m_cfCopyFiles;
    m_cfCopyFiles = new CopyFiles(this);

    m_cfCopyFiles->show();
    m_cfCopyFiles->setFilesDir(m_lfwLoadFileWidget->getDir());
    m_cfCopyFiles->setStructList(m_qlCopyList);
    QCoreApplication::processEvents();
    m_cfCopyFiles->startCopy();

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
}

void MainWindow::aboutSlot()
{
    About* about = nullptr;

    about = new About(this);
    about->exec();

    delete about;
}
