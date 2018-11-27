// This file is part of Update.

//  Update is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  any later version.

//  Update is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
//  along with Update.  If not, see <https://www.gnu.org/licenses/>.

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
