#ifndef FILECOPYITEM_H
#define FILECOPYITEM_H

#include <QObject>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QList>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QThread>
#include <QShowEvent>
#include <QMessageBox>
#include <QProcess>
#include <QDate>

#include "pushbutton.h"
#include "define.h"
#include "threadcopy.h"
#include "copyinfomation.h"

class FileCopyItem : public QWidget
{
    Q_OBJECT
public:
    explicit FileCopyItem(QWidget *parent = 0,QStringList* files = nullptr,QDir filesDir=QDir(NULLDIR),QDir dest = QDir(NULLDIR),bool createCopy=false);
    ~FileCopyItem();
    void startCopy();
    void stopCopy();
    void reset();
    bool getSuccess();

private:
    QStringList m_qslFiles;
    QDir m_qdDest;
    QDir m_qdFilesDir;
    bool m_bCreateCopy;
    QHBoxLayout* m_qhblMainLayout;
    QHBoxLayout* m_qvbLeftTop;
    QVBoxLayout* m_qvbLeft;
    QVBoxLayout* m_qvbRight;
    QLabel* m_qlName;
    QProgressBar* m_qpbProgressBar;
    PushButton* m_pbState;
    PushButton* m_pbInfo;
    QString m_qsCopyResult;
    ThreadCopy* m_tcThreadCopy;
    bool m_repeatClicked;
    bool m_repeatOk;

private slots:
    void repeatSlot();
    void infoSlot();
    void endSlot(QString errorReport);

signals:
    void copyFinished(bool first, bool continueCopy);
};

#endif // FILECOPYITEM_H
