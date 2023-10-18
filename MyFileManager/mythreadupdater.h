#ifndef MYTHREADUPDATER_H
#define MYTHREADUPDATER_H

#include <QStringList>
#include <QObject>
#include <QThread>
#include <QDir>

class MyThreadUpdater : public QThread
{
    Q_OBJECT
public:
    MyThreadUpdater(QStringList names, QStringList *dev_path, QObject *parent = nullptr);
    void stop();

protected:
    void run();

private:
    volatile bool stoped;
    QStringList *paths;
    QStringList dev_names;

signals:

};//class MyThreadUpdater : public QThread

#endif // MYTHREADUPDATER_H
