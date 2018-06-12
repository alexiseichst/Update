#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QRect>
#include <QList>
#include <QDir>

#include "define.h"

struct COPYSTRUCT
{
    QDir Destdir;
    QStringList FileList;
    qlonglong Id;
    bool createCopy;
};

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    void save(QRect *windowsRect,QList<COPYSTRUCT*>* list,QString filesDir);
    void load(QRect *windowsRect,QList<COPYSTRUCT*>* list,QString* filesDir);

private:
    QSettings* m_qsSettings;
};

#endif // SETTINGS_H
