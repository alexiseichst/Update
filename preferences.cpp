#include "preferences.h"

Preferences::Preferences(QList<PREFSTRUCT*>* prefList,QWidget *parent,bool onlyRead) : QDialog(parent)
{
    m_qlPrefList=prefList;
    for (int iTab=0;iTab<m_qlPrefList->size();iTab++)
        delete m_qlPrefList->at(iTab);
    m_qlPrefList->clear();

    m_qPreferences = new QSettings("AutoSelect.sel", QSettings::IniFormat,this);
    readFile();

    if (onlyRead)
    {
        hide();
        return;
    }
    else
    {
        QFont font;
        QPalette pal = palette();
        QPixmap pixmap(":/Icon/compose.png");
        QIcon icon(pixmap);
        resize(450,450);
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        setModal(true);
        pal.setColor(QPalette::Background, Qt::white);
        setAutoFillBackground(true);
        setPalette(pal);
        setWindowTitle("Selection automatique");
        setWindowIcon(icon);

        m_qvbMainLayout = new QVBoxLayout(this);
        this->setLayout(m_qvbMainLayout);

        m_qtvTableWidget = new QTabWidget(this);
        m_qvbMainLayout->addWidget(m_qtvTableWidget);

        for (int iTab=0;iTab<m_qlPrefList->size();iTab++)
        {
            m_qlPrefTabList.append(new PreferenceTab(this,m_qlPrefList->at(iTab),iTab));
            m_qtvTableWidget->addTab(m_qlPrefTabList.last(),m_qlPrefList->at(iTab)->tabName);
            connect(m_qlPrefTabList.at(iTab),SIGNAL(tabTextChangeSignal(QString,int)),this,SLOT(tabTextChangeSlot(QString,int)));
        }
        m_qlPrefList->append(new PREFSTRUCT);
        m_qlPrefList->last()->tabName=NEWTAB;
        m_qlPrefList->last()->allDll=false;
        m_qlPrefList->last()->allExe=false;
        m_qlPrefTabList.append(new PreferenceTab(this,m_qlPrefList->last(),m_qlPrefTabList.size()));
        connect(m_qlPrefTabList.last(),SIGNAL(tabTextChangeSignal(QString,int)),this,SLOT(tabTextChangeSlot(QString,int)));
        m_qtvTableWidget->addTab(m_qlPrefTabList.last(),NEWTAB);
    }
}

Preferences::~Preferences()
{
    for (int iTab=0;iTab<m_qlPrefTabList.size();iTab++)
    {
        m_qlPrefTabList.at(iTab)->saveConf();
        m_qlPrefList->at(iTab)->tabName = m_qtvTableWidget->tabText(iTab);
    }
    for (int iStruct=0;iStruct<m_qlPrefList->size();iStruct++)
    {
        if (!m_qlPrefList->at(iStruct)->files.size() && !m_qlPrefList->at(iStruct)->names.size())
        {
            m_qlPrefList->removeAt(iStruct);
        }
    }
    writeFile();
}

void Preferences::tabTextChangeSlot(QString text,int id)
{
    m_qtvTableWidget->setTabText(id,text);
}

void Preferences::writeFile()
{
    m_qPreferences->clear();

    m_qPreferences->setValue("General/NbStruct",m_qlPrefList->size());

    for (int iStruct=0;iStruct<m_qlPrefList->size();iStruct++)
    {
        m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"NbNames",m_qlPrefList->at(iStruct)->names.size());
        for (int iNames=0;iNames<m_qlPrefList->at(iStruct)->names.size();iNames++)
        {
            if (m_qlPrefList->at(iStruct)->names.at(iNames)!="")
            {
                m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"Name"+QString::number(iNames),m_qlPrefList->at(iStruct)->names.at(iNames));
            }
            else
            {
                m_qlPrefList->at(iStruct)->names.removeAt(iNames);
                m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"NbNames",m_qlPrefList->at(iStruct)->names.size());
            }
        }

        m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"NbFiles",m_qlPrefList->at(iStruct)->files.size());
        for (int iNames=0;iNames<m_qlPrefList->at(iStruct)->files.size();iNames++)
        {
            if (m_qlPrefList->at(iStruct)->files.at(iNames)!="")
            {
                m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"Files"+QString::number(iNames),m_qlPrefList->at(iStruct)->files.at(iNames));
            }
            else
            {
                m_qlPrefList->at(iStruct)->files.removeAt(iNames);
                m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"NbFiles",m_qlPrefList->at(iStruct)->files.size());

            }
        }
        m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"AllDll",m_qlPrefList->at(iStruct)->allDll);
        m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"AllExe",m_qlPrefList->at(iStruct)->allExe);
        m_qPreferences->setValue("General/Struct"+QString::number(iStruct)+"TabName",m_qlPrefList->at(iStruct)->tabName);
    }
}

void Preferences::readFile()
{
    int NbStruct=0;

    NbStruct = m_qPreferences->value("General/NbStruct","0").toInt();

    for (int iStruct=0;iStruct<NbStruct;iStruct++)
    {
        PREFSTRUCT newStrcut;
        int nbTmp=0;

        nbTmp = m_qPreferences->value("General/Struct"+QString::number(iStruct)+"NbNames","0").toInt();
        for (int iNames=0;iNames<nbTmp;iNames++)
        {
            newStrcut.names.append(m_qPreferences->value("General/Struct"+QString::number(iStruct)+"Name"+QString::number(iNames),"Error").toString());
        }

        nbTmp = m_qPreferences->value("General/Struct"+QString::number(iStruct)+"NbFiles","0").toInt();
        for (int iFiles=0;iFiles<nbTmp;iFiles++)
        {
            newStrcut.files.append(m_qPreferences->value("General/Struct"+QString::number(iStruct)+"Files"+QString::number(iFiles),"Error").toString());
        }
        newStrcut.allDll = m_qPreferences->value("General/Struct"+QString::number(iStruct)+"AllDll","0").toBool();
        newStrcut.allExe = m_qPreferences->value("General/Struct"+QString::number(iStruct)+"AllExe","0").toBool();
        newStrcut.tabName = m_qPreferences->value("General/Struct"+QString::number(iStruct)+"TabName","Nouveau").toString();

        if (newStrcut.files.size() || newStrcut.names.size())
        {
            m_qlPrefList->append(new PREFSTRUCT);
            *m_qlPrefList->last() = newStrcut;
        }
    }
}
