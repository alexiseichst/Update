#include "preferencetab.h"

PreferenceTab::PreferenceTab(QWidget *parent,PREFSTRUCT* prefStruct,int tabId) : QWidget(parent)
{
    m_plPrefStruct=prefStruct;
    m_iTabId=tabId;

    m_qhblMainLayout = new QVBoxLayout();
    setLayout(m_qhblMainLayout);

    m_qleNameEdit=new QLineEdit(m_plPrefStruct->tabName,this);
    m_qleNameEdit->setAlignment(Qt::AlignCenter);
    connect(m_qleNameEdit,SIGNAL(textChanged(QString)),this,SLOT(tabTextChangeSlot(QString)));

    m_qhblMainLayout->addWidget(m_qleNameEdit);

    m_qhblListLayout = new QHBoxLayout();
    m_qhblMainLayout->addLayout(m_qhblListLayout);

    m_qvblFolderNames = new QVBoxLayout();
    m_qhblListLayout->addLayout(m_qvblFolderNames);
    m_qlvFolderList = new ListViewPreference(this);
    m_qvblFolderNames->addWidget(m_qlvFolderList);

    m_qvblFilesNames = new QVBoxLayout();
    m_qhblListLayout->addLayout(m_qvblFilesNames);
    m_qlvFilesList = new ListViewPreference(this);
    m_qvblFilesNames->addWidget(m_qlvFilesList);
    m_qpbAllExe = new QPushButton("Tous les exe");
    m_qpbAllExe->setCheckable(true);
    m_qvblFilesNames->addWidget(m_qpbAllExe);
    m_qpbAllDll = new QPushButton("Toutes les dll");
    m_qpbAllDll->setCheckable(true);
    m_qvblFilesNames->addWidget(m_qpbAllDll);

    for (int item=0;item<m_plPrefStruct->names.size();item++)
    {
        m_qlvFolderList->addNewItem(item,m_plPrefStruct->names.at(item));
    }

    for (int item=0;item<m_plPrefStruct->files.size();item++)
    {
        m_qlvFilesList->addNewItem(item,m_plPrefStruct->files.at(item));
    }
    m_qpbAllExe->setChecked(m_plPrefStruct->allExe);
    m_qpbAllDll->setChecked(m_plPrefStruct->allDll);

    m_qleNameEdit->setText(m_plPrefStruct->tabName);
}

void PreferenceTab::saveConf()
{
    QStringList names;
    QStringList files;

    for (int item=0;item<m_qlvFolderList->count();item++)
    {
        names.append(m_qlvFolderList->item(item)->text());
    }

    for (int item=0;item<m_qlvFilesList->count();item++)
    {
        files.append(m_qlvFilesList->item(item)->text());
    }

    m_plPrefStruct->files = files;
    m_plPrefStruct->names = names;
    m_plPrefStruct->allDll = m_qpbAllDll->isChecked();
    m_plPrefStruct->allExe = m_qpbAllExe->isChecked(); 
}

void PreferenceTab::tabTextChangeSlot(QString text)
{
    emit tabTextChangeSignal(text,m_iTabId);
}
