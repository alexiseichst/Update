#ifndef THREADCOPY_H
#define THREADCOPY_H

#include <QObject>

class ThreadCopy : public QObject
{
    Q_OBJECT
public:
    explicit ThreadCopy(QObject *parent = 0);

signals:

public slots:
};

#endif // THREADCOPY_H