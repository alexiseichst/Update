#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QRect>
#include <QList>

#include "define.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    QSettings* m_qsSettings;
    QRect m_WindowRect;

    QList<bool> m_qlDayDiplay;


    void save();
    void load();
signals:

public slots:
};

#endif // SETTINGS_H
