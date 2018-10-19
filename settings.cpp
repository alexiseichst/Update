#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_qsSettings = new QSettings("Update.ini", QSettings::IniFormat,this);
}

void Settings::save(QRect *windowsRect,QList<COPYSTRUCT*>* list,QString filesDir)
{
    addLog("Sauvegarde dans le .ini");

    m_qsSettings->clear();

    m_qsSettings->setValue("General/WindowRectX",windowsRect->x());
    m_qsSettings->setValue("General/WindowRectY",windowsRect->y());
    m_qsSettings->setValue("General/WindowRectHeight",windowsRect->height());
    m_qsSettings->setValue("General/WindowRectWidth",windowsRect->width());

    if (!list->size())
        return;
    m_qsSettings->setValue("Destination/nbDest",list->size());
    for (int iList=0;iList<list->size();iList++)
    {
        m_qsSettings->setValue("Destination"+QString::number(iList)+"/ID",list->at(iList)->Id);
        m_qsSettings->setValue("Destination"+QString::number(iList)+"/DestPath",list->at(iList)->Destdir.path());
        m_qsSettings->setValue("Destination"+QString::number(iList)+"/CreateCopy",list->at(iList)->createCopy);
        m_qsSettings->setValue("Destination"+QString::number(iList)+"/NbFiles",list->at(iList)->FileList.size());
        for (int iStringList=0;iStringList<list->at(iList)->FileList.size();iStringList++)
        {
             m_qsSettings->setValue("Destination"+QString::number(iList)+"/Files"+QString::number(iStringList),list->at(iList)->FileList.at(iStringList));
        }
    }
    if (filesDir!=NULLDIR)
        m_qsSettings->setValue("Destination/filesDir",filesDir);
}

void Settings::load(QRect *windowsRect,QList<COPYSTRUCT*>* list,QString* filesDir)
{
    addLog("Lecture du .ini");

    int nbDest=0;
    int nbFile=0;

    windowsRect->setX(m_qsSettings->value("General/WindowRectX","200").toInt());
    windowsRect->setY(m_qsSettings->value("General/WindowRectY","200").toInt());
    windowsRect->setHeight(m_qsSettings->value("General/WindowRectHeight","600").toInt());
    windowsRect->setWidth(m_qsSettings->value("General/WindowRectWidth","800").toInt());

    nbDest = m_qsSettings->value("Destination/nbDest","0").toInt();

    for (int iDest=0;iDest<nbDest;iDest++)
    {
        list->append(new COPYSTRUCT);
        list->last()->Id = m_qsSettings->value("Destination"+QString::number(iDest)+"/ID","0").toLongLong();
        list->last()->createCopy = m_qsSettings->value("Destination"+QString::number(iDest)+"/CreateCopy","0").toBool();
        list->last()->Destdir = QDir(m_qsSettings->value("Destination"+QString::number(iDest)+"/DestPath","Erreur").toString());
        nbFile = m_qsSettings->value("Destination"+QString::number(iDest)+"/NbFiles","0").toInt();
        for (int iStringList=0;iStringList<nbFile;iStringList++)
        {
            list->last()->FileList.append(m_qsSettings->value("Destination"+QString::number(iDest)+"/Files"+QString::number(iStringList),"Erreur").toString());
        }
    }
    *filesDir = m_qsSettings->value("Destination/filesDir",NULLDIR).toString();
}
