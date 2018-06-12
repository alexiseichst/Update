#include "settings.h"

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_qsSettings = new QSettings("Activity_Report.ini", QSettings::IniFormat,this);

    for (int i=0;i<7;i++)
        m_qlDayDiplay.append(true);

    load();
}

Settings::~Settings()
{
    save();
}

void Settings::save()
{
    m_qsSettings->setValue("General/WindowRectX",QString::number(m_WindowRect.x()));
    m_qsSettings->setValue("General/WindowRectY",QString::number(m_WindowRect.y()));
    m_qsSettings->setValue("General/WindowRectHeight",QString::number(m_WindowRect.height()));
    m_qsSettings->setValue("General/WindowRectWidth",QString::number(m_WindowRect.width()));

    for (int i=0;i<7;i++)
        m_qsSettings->setValue("Days/DisplayDay"+QString::number(i),QString::number(m_qlDayDiplay.at(i)));
}

void Settings::load()
{
    m_WindowRect.setX(m_qsSettings->value("General/WindowRectX","100").toInt());
    m_WindowRect.setY(m_qsSettings->value("General/WindowRectY","100").toInt());
    m_WindowRect.setHeight(m_qsSettings->value("General/WindowRectHeight","600").toInt());
    m_WindowRect.setWidth(m_qsSettings->value("General/WindowRectWidth","800").toInt());

    for (int i=0;i<7;i++)
        m_qlDayDiplay.replace(i,m_qsSettings->value("Days/DisplayDay"+QString::number(i),QString::number(1)).toInt());
}
