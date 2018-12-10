#include "fileiconprovider.h"

FileIconProvider::FileIconProvider(QObject *parent) : QObject(parent)
{
    bool ok=false;

    m_nbIcon=0;
    m_iconNames.clear();
    m_iconsDir.setPath(QDir::currentPath()+"/"+FOLDER_NAME_ICON);

    if(!m_iconsDir.exists())
    {
        m_iconsDir.mkdir(m_iconsDir.path());
    }
    else
    {
        m_iconNames = QStringList(m_iconsDir.entryList(QStringList() << "*.png",QDir::Files));
    }
}

QIcon FileIconProvider::icon(QFileInfo fileInfo)
{
    QIcon rt;
    QFileIconProvider provider;
    int iIcon=0,tmpPos=0;
    QString name;

    tmpPos = fileInfo.fileName().lastIndexOf("/");
    name = fileInfo.fileName().mid(tmpPos,fileInfo.fileName().size()-tmpPos);
    name.remove(".");
    name.append(".png");
    iIcon=m_iconNames.indexOf(name);
    if (iIcon<0)
    {
        rt=provider.icon(fileInfo);
        if (m_iconsDir.exists())
        {
            QPixmap pixmap = rt.pixmap(rt.availableSizes().last());
            pixmap.save(m_iconsDir.path()+"/"+name,"PNG");
        }
    }
    else
    {
        QPixmap pixmap;
        pixmap.load(m_iconsDir.path()+"/"+name,"PNG");
        rt = pixmap;
    }

    return rt;
}
