#include "mythreadupdater.h"

MyThreadUpdater::MyThreadUpdater(QStringList names, QStringList *dev_path, QObject *parent)
    : QThread(parent), stoped(false), paths(dev_path), dev_names(names)
{
    paths->clear();
}//MyThreadUpdater(QStringList names, QStringList *dev_path, QObject *parent = nullptr)

void MyThreadUpdater::stop()
{
    stoped = true;
}//void stop()

void MyThreadUpdater::run()
{
    QStringList dirlist;
    if(QSysInfo::productType() == "windows")
    {
        QFileInfoList drivers = QDir::drives();
        for (auto i : drivers)
            dirlist << i.path();
    }else dirlist << QDir("/").path();
    for (; !stoped;) {
        QDir dir(dirlist.at(0));
        QStringList downDir = dir.entryList(QDir::Dirs);
        for (auto name : dev_names)
            for (auto i : downDir)
                if (name == i) *paths << dirlist.at(0) + i;
        if (dev_names.size() == paths->size()) stop();
        else paths->clear();
        for (auto i : downDir)
            dirlist << dirlist.at(0) + i + '/';
        dirlist.removeAt(0);
    }//for (; !stoped;)
}//void run()
