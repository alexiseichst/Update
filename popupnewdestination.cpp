#include "popupnewdestination.h"

PopUpNewDestination::PopUpNewDestination(QWidget *parent,QDir dir,bool createCopy) : QDialog(parent)
{   
    QFont font;
    QPalette pal = palette();
    QPixmap pixmap(":/Icon/add.png");
    QIcon icon(pixmap);


    m_qdCurrentFolder.setPath(NULLDIR);
    m_bNew=true;

    setModal(true);
    setMaximumSize(300,250);
    setMinimumSize(300,250);
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    setWindowTitle("New Folder");
    setWindowIcon(icon);

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

    m_qlValidFolderPath = new PushButton(this,":/Icon/error.png",false);
    m_qlValidFolderPath->setToolTip("Error");
    m_qlValidFolderPath->setMinimumSize(22,22);
    m_qlValidFolderPath->setIconSize(QSize(22,22));
    m_qvblPathLayout->addWidget(m_qlValidFolderPath);

    m_qleFolderPath = new QLineEdit(this);
    m_qleFolderPath->setStyleSheet(" QLineEdit {border: 2px solid gray;border-radius: 5px;padding: 0 8px;}");
    m_qleFolderPath->setMinimumWidth(200);
    m_qvblPathLayout->addWidget(m_qleFolderPath);
    connect(m_qleFolderPath,SIGNAL(textChanged(QString)),this,SLOT(LineFolderPathChangeSlot()));

    m_qpbOpenFolerPath = new PushButton(this,":/Icon/folder.png");
    m_qpbOpenFolerPath->setToolTip("Open new folder");
    connect(m_qpbOpenFolerPath,SIGNAL(clicked(bool)),this,SLOT(OpenFolerPathClickedSlot()));
    m_qpbOpenFolerPath->setMinimumSize(22,22);
    m_qpbOpenFolerPath->setIconSize(QSize(22,22));
    m_qvblPathLayout->addWidget(m_qpbOpenFolerPath);

    m_qvblMainLayout->addSpacing(20);
    m_qcbCreateCopy = new QCheckBox("Create copy with date",this);
    m_qcbCreateCopy->setChecked(createCopy);
    m_qvblMainLayout->addWidget(m_qcbCreateCopy);

    mqdbButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,this);
    m_qvblMainLayout->addWidget(new QLabel(this));
    m_qvblMainLayout->addWidget(mqdbButtons);
    mqdbButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(mqdbButtons, SIGNAL(clicked(QAbstractButton*)), this, SLOT(DialogBoxButtonSlot(QAbstractButton*)));

    connect(this, SIGNAL(finished(int)), this, SLOT(ExitSlot()));

    if (dir.path()!=NULLDIR)
    {
        NewDir(dir.path());
        NewFolder(true);
        m_qcbCreateCopy->setChecked(createCopy);
        m_bNew=false;
    }  
    show();
}

void PopUpNewDestination::OpenFolerPathClickedSlot()
{
    QString dir = "";

    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/");

    if (dir!="")
    {
        NewDir(dir);
        NewFolder(true);
    }
}

void PopUpNewDestination::NewDir(QString path)
{
    QDir dir(path);

    if (dir.exists() && path!=NULLDIR)
    {
        m_qdCurrentFolder.setPath(path);
    }
    else
    {
        m_qdCurrentFolder.setPath(NULLDIR);
    }
}
void PopUpNewDestination::LineFolderPathChangeSlot()
{
     NewDir(m_qleFolderPath->text());
     NewFolder(false);
}

void PopUpNewDestination::NewFolder(bool setText)
{

     m_qlValidFolderPath->setIconCustom(":/Icon/error.png");
     m_qlValidFolderPath->setToolTip("Error");
     mqdbButtons->button(QDialogButtonBox::Ok)->setEnabled(false);

    if (m_qdCurrentFolder.path()==NULLDIR)
        return;

    if (setText)
        m_qleFolderPath->setText(m_qdCurrentFolder.path());

    m_qlName->setText(m_qdCurrentFolder.dirName());
    m_qlValidFolderPath->setIconCustom(":/Icon/success.png");
    m_qlValidFolderPath->setToolTip("Success");
    mqdbButtons->button(QDialogButtonBox::Ok)->setEnabled(true);

}

void PopUpNewDestination::DialogBoxButtonSlot(QAbstractButton* button)
{
    if (button == mqdbButtons->button(QDialogButtonBox::Ok))
    {
       disconnect(this, SIGNAL(finished(int)), this, SLOT(ExitSlot()));
       ExitSlot(true);
    }
    else
    {
       ExitSlot();
    }
}
void PopUpNewDestination::ExitSlot(bool ok)
{
    if (m_bNew && !ok)
        m_qdCurrentFolder.setPath(NULLDIR);
    close();
}

QDir PopUpNewDestination::getQDir()
{
    return m_qdCurrentFolder;
}

bool PopUpNewDestination::getCreateCopy()
{
    return m_qcbCreateCopy->isChecked();
}

