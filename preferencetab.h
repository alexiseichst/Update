#ifndef PreferenceTab_H
#define PreferenceTab_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include <QLineEdit>

#include "define.h"

#include "listviewpreference.h"

struct PREFSTRUCT
{
    QString tabName;
    QStringList names;
    QStringList files;
    bool allDll;
    bool allExe;
};

class PreferenceTab : public QWidget
{
    Q_OBJECT
public:
    explicit PreferenceTab(QWidget *parent = 0,PREFSTRUCT* prefList=nullptr,int tabId=0);
    void saveConf();

private:
   QVBoxLayout* m_qhblMainLayout;
   QLineEdit* m_qleNameEdit;

   QHBoxLayout* m_qhblListLayout;

   QVBoxLayout* m_qvblFolderNames;
   ListViewPreference* m_qlvFolderList;

   QVBoxLayout* m_qvblFilesNames;
   ListViewPreference* m_qlvFilesList;
   QPushButton* m_qpbAllExe;
   QPushButton* m_qpbAllDll;

   PREFSTRUCT* m_plPrefStruct;

   int m_iTabId;

signals:
   void tabTextChangeSignal(QString text,int id);

private slots:
   void tabTextChangeSlot(QString text);
};

#endif // PreferenceTab_H
