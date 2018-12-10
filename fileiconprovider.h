#ifndef FILEICONPROVIDER_H
#define FILEICONPROVIDER_H

#include <QObject>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QApplication>

#define FOLDER_NAME_ICON "icons"

class FileIconProvider : public QObject
{
    Q_OBJECT
public:
    explicit FileIconProvider(QObject *parent = nullptr);
    QIcon icon(QFileInfo fileInfo);

private:
    QFileIconProvider* m_FileIconProvider;
    QDir m_iconsDir;

    int m_nbIcon;
    QStringList m_iconNames;

signals:

public slots:
};

#endif // FILEICONPROVIDER_H
