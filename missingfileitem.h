#ifndef MISSINGFILEITEM_H
#define MISSINGFILEITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>

class MissingFileItem : public QWidget
{
    Q_OBJECT
public:
    explicit MissingFileItem(QWidget *parent = 0,QString name="Erreur");

    bool getIgnored();
    void setIgnored(bool ignore);

private:
    QHBoxLayout* m_qhblMainLayout;
    QLabel* m_qlName;
    QPushButton* m_qpbDelete;

signals:

public slots:

private slots:
    void OnDeleteButtonClicked(bool checked);
};

#endif // MISSINGFILEITEM_H
