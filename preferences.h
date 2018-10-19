#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QIcon>
#include <QStringList>
#include <QList>
#include <QSettings>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QTabBar>
#include <QToolButton>
#include <PreferenceTab.h>

#include "define.h"

#define NEWTAB "Nouveau"

class Preferences : public QDialog
{
    Q_OBJECT
public:
    explicit Preferences(QList<PREFSTRUCT*>* prefList=nullptr,QWidget *parent = 0,bool onlyRead=false);
    ~Preferences();

private:
    QList<PREFSTRUCT*>* m_qlPrefList;
    QSettings* m_qPreferences;
    QVBoxLayout* m_qvbMainLayout;
    QTabWidget* m_qtvTableWidget;
    QList<PreferenceTab*> m_qlPrefTabList;

    void writeFile();
    void readFile();

signals:

public slots:
    void tabTextChangeSlot(QString text,int id);
};

#endif // PREFERENCES_H
