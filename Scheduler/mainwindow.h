#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QtUiTools/QUiLoader>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QModelIndex>
#include <QTextStream>
#include <QKeyEvent>
#include <QProcess>
#include <QFile>

//#include "ui_addform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void saveModelData(QTextStream &s);
    void setModelData(QTextStream &s);
    ~MainWindow() override;

protected:
    void keyReleaseEvent(QKeyEvent *e) override;

private slots:
    void on_actionAdd_triggered();
    void on_actionDelete_triggered();
    void on_actionAbout_triggered();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_actionExit_triggered();
    void on_actionEdit_triggered(bool checked);
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m;
};//class MainWindow : public QMainWindow
#endif // MAINWINDOW_H
