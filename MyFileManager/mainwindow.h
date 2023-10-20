#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QStandardPaths>
#include <QStandardItem>
#include <QStorageInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLineEdit>
#include <QString>
#include <QStack>
#include <QTimer>
#include <QDir>

#include "mythreadupdater.h"

#define STACK_MAX_SIZE 50

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum favourDir {HOME = 0, DESKTOP, VIDEO, DOCUMENTS, DOWNLOAD, IMAGES, MUSIC, BASKET};

public:
    MainWindow(QWidget *parent = nullptr);
    void pushChanges(QStack<QString> &st, QString ch);
    inline QStandardPaths::StandardLocation favourDirTransform(int dir);
    ~MainWindow();

private slots:
    void on_actionFullScreen_triggered();
    void on_actionExit_triggered();
    void on_listView_doubleClicked(const QModelIndex &index);
    void on_path_returnPressed();
    void on_actionView_triggered();
    void on_actionBack_triggered();
    void on_actionForward_triggered();
    void on_actionAbout_triggered();
    void on_favour_clicked(const QModelIndex &index);
    void on_timer();
    void on_user_favour_clicked(const QModelIndex &index);
    void on_device_clicked(const QModelIndex &index);

private:

    QStandardItemModel *favour;
    int16_t device_count = 0;
    QFileSystemModel *model;
    MyThreadUpdater *thread;
    QStringList device_path;
    QStack<QString> forvard;
    QStack<QString> back;
    Ui::MainWindow *ui;
    QLineEdit *path;
    QTimer *timer;
};//class MainWindow : public QMainWindow
#endif // MAINWINDOW_H
