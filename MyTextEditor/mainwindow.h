#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMdiSubWindow>
#include <QPrintDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QFile>

#include "mytimedatedialog.h"
#include "mytabledialog.h"
#include "mysubwindow.h"
#include "mytextedit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setLabelsText(QString text);

private slots:
    void on_actionFullScreen_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionAbout_triggered();
    void on_open_triggered();
    void on_save_triggered();
    void on_open_read_only_triggered();
    void on_actionExit_triggered();
    void on_actionDayNight_triggered();
    void on_actionPrint_triggered();
    void on_actionNewWindow_triggered();
    void on_actionaddTable_triggered();
    void on_actionSettings_triggered(bool checked);
    void on_actionCopyFormat_triggered(bool checked);
    void on_actionFont_triggered();
    void on_actionAlignment_triggered(bool checked);
    void on_actionAlRight_triggered();
    void on_actionAlLeft_triggered();
    void on_actionAlCentr_triggered();
    void on_actionAlWidth_triggered();

    void on_actionPaste_triggered(bool checked);

    void on_actionDateTime_triggered();

private:
    Ui::MainWindow *ui;
    bool NightMode = false;
};//class MainWindow
#endif // MAINWINDOW_H
