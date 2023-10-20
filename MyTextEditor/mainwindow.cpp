#include "mainwindow.h"
#include "ui_mainwindow.h"

#define ACTIVESUBWIN static_cast<MySubWindow*>(ui->mdiArea->activeSubWindow()->widget())

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionDayNight->setVisible(false);
    ui->actionFont->setVisible(false);
    ui->actionAlLeft->setVisible(false);
    ui->actionAlCentr->setVisible(false);
    ui->actionAlRight->setVisible(false);
    ui->actionAlWidth->setVisible(false);
    ui->actionaddTable->setVisible(false);
    ui->actionDateTime->setVisible(false);

    on_actionNewWindow_triggered();
}//MainWindow(QWidget *parent = nullptr)

MainWindow::~MainWindow()
{
    delete ui;
}//~MainWindow()

void MainWindow::setLabelsText(QString text)
{
    for (auto i : ui->mdiArea->subWindowList())
        static_cast<MySubWindow*>(i->widget())->setLabelText(text);
}//void setLabelsText(QString text)

void MainWindow::on_actionFullScreen_triggered()
{
    if (isFullScreen()) {
        showNormal();
        ui->actionFullScreen->setIcon(QIcon(":/icons/icons/fullScreen.png"));
    } else {
        showFullScreen();
        ui->actionFullScreen->setIcon(QIcon(":/icons/icons/fullScreenOff.png"));
    }//if (isFullScreen())
}//on_actionFullScreen_triggered()

void MainWindow::on_actionUndo_triggered()
{
    ACTIVESUBWIN->undo();
}//on_actionUndo_triggered()

void MainWindow::on_actionRedo_triggered()
{
    ACTIVESUBWIN->redo();
}//on_actionRedo_triggered()

void MainWindow::on_actionAbout_triggered()
{
    QFile file(":/about.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        ACTIVESUBWIN->printText(stream, true);
        file.close();
    }//if (file.open(QIODevice::ReadOnly | QIODevice::Text))
}//on_actionAbout_triggered()

void MainWindow::on_open_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл для открытия", QDir::current().path(),
                                                    QString("Текстовый файл(*.txt);;Бинарный файл(*.binary);;Все файлы(*.*)"));
    if (filename.length()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            bool is_binary = (filename.right(7) == ".binary");
            ACTIVESUBWIN->printText(stream, is_binary, false);
            file.close();
        }//if (file.open(..))
    } else QMessageBox::information(this, "Ошибка чтения файла", "Не удалось считать выбранный файл.");
}//on_open_triggered()

void MainWindow::on_save_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Выберите файл для сохранения", QDir::current().path(),
                                                    QString("Текстовый файл(*.txt);;Бинарный файл(*.binary)"));
    if (filename.length()) {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            bool is_binary = (filename.right(7) == ".binary");
            ACTIVESUBWIN->scanText(stream, is_binary);
            file.close();
        }//if (file.open(..))
    }else QMessageBox::information(this, "Ошибка записи файла", "Не удалось записать данные в выбранный файл.");
}//on_save_triggered()

void MainWindow::on_open_read_only_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите файл для открытия", QDir::current().path(),
                                                    QString("Текстовый файл(*.txt);;Бинарный файл(*.binary);;Все файлы(*.*)"));
    if (filename.length()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            bool is_binary = (filename.right(7) == ".binary");
            ACTIVESUBWIN->printText(stream, is_binary, true);
            file.close();
        }//if (file.open(..))
    } else QMessageBox::information(this, "Ошибка чтения файла", "Не удалось считать выбранный файл.");
}//on_open_read_only_triggered()

void MainWindow::on_actionExit_triggered()
{
    close();
}//on_actionExit_triggered()

void MainWindow::on_actionDayNight_triggered()
{
    if (NightMode) {
        ui->actionDayNight->setIcon(QIcon(":/icons/icons/classic.png"));
        qApp->setStyleSheet("");
        ui->mdiArea->setBackground(QBrush(QColor("#9C9C9C")));
        setLabelsText("<FONT COLOR=#000000>Author:</FONT>");
        NightMode = false;
    } else {
        QFile file(":/night.css");
        if (file.open(QIODevice::ReadOnly)) {
            ui->actionDayNight->setIcon(QIcon(":/icons/icons/night.png"));
            QString style = file.readAll();
            qApp->setStyleSheet(style);
            ui->mdiArea->setBackground(QBrush(QColor("#374463")));
            setLabelsText("<FONT COLOR=#A6B4B5>Author:</FONT>");
            file.close();
            NightMode = true;
        }//if (file.open(QIODevice::ReadOnly))
    }//if (NightMode)
}//on_actionDayNight_triggered()

void MainWindow::on_actionPrint_triggered()
{
    QPrinter p;
    QPrintDialog pdlg(&p,this);
    pdlg.setWindowTitle("Печать");
    if (pdlg.exec() != QDialog::Accepted) return;
    ACTIVESUBWIN->print(&p);
}//on_actionPrint_triggered()

void MainWindow::on_actionNewWindow_triggered()
{
    MySubWindow *subwindow = new MySubWindow(ui->mdiArea);
    subwindow->setObjectName(QString::fromUtf8("subwindow"));

    NightMode? subwindow->setLabelText("<FONT COLOR=#A6B4B5>Author:</FONT>"):
               subwindow->setLabelText("<FONT COLOR=#000000>Author:</FONT>");

    connect(subwindow, SIGNAL(charFormatChanged(bool)), this, SLOT(on_actionCopyFormat_triggered(bool)));

    ui->mdiArea->addSubWindow(subwindow);
    subwindow->show();
}//on_actionNewWindow_triggered()

void MainWindow::on_actionaddTable_triggered()
{
    MyTableDialog *dialog = new MyTableDialog (this);
    if (dialog->exec() == QDialog::Accepted) {
        DataNM data = dialog->getData();
        ACTIVESUBWIN->insertTable(data.n, data.m);
    }//if (dialog->exec() == QDialog::Accepted)
    delete dialog;
}//on_actionaddTable_triggered()

void MainWindow::on_actionSettings_triggered(bool checked)
{
    ui->actionDayNight->setVisible(checked);
    ui->actionFont->setVisible(checked);
}//on_actionSettings_triggered(bool checked)

void MainWindow::on_actionCopyFormat_triggered(bool checked)
{
    if (checked) {
        ACTIVESUBWIN->setCursor(QCursor(QPixmap(":/icons/icons/fomat_cursor.png")));
        ACTIVESUBWIN->saveTextFormat();
        ACTIVESUBWIN->setFormatNeedsInserted(checked);
    } else {
        ui->actionCopyFormat->setChecked(checked);
        ACTIVESUBWIN->setCursor(QCursor(Qt::CursorShape::IBeamCursor));
    }
}//on_actionCopyFormat_triggered(bool checked)

void MainWindow::on_actionFont_triggered()
{
    QFont font = ACTIVESUBWIN->getTextFormat().font();
    QFontDialog fdlg(font, this);
    bool b[] = {true};
    font = fdlg.getFont(b);
    if (b[0]) {
        QTextCharFormat f;
        f.setFont(font);
        ACTIVESUBWIN->setTextFormat(f);
    }//if (b[0])
}//on_actionFont_triggered()

void MainWindow::on_actionAlignment_triggered(bool checked)
{
    ui->actionAlLeft->setVisible(checked);
    ui->actionAlCentr->setVisible(checked);
    ui->actionAlRight->setVisible(checked);
    ui->actionAlWidth->setVisible(checked);
}//on_actionAlignment_triggered(bool checked)

void MainWindow::on_actionAlRight_triggered()
{
    ui->actionAlignment->setIcon(QIcon(":/icons/alignment_right.png"));
    ACTIVESUBWIN->setAlign(Qt::AlignRight);
    ui->actionAlignment->trigger();
}//on_actionAlRight_triggered()

void MainWindow::on_actionAlLeft_triggered()
{
    ui->actionAlignment->setIcon(QIcon(":/icons/alignment_left.png"));
    ACTIVESUBWIN->setAlign(Qt::AlignLeft);
    ui->actionAlignment->trigger();
}//on_actionAlLeft_triggered()

void MainWindow::on_actionAlCentr_triggered()
{
    ui->actionAlignment->setIcon(QIcon(":/icons/alignment_center.png"));
    ACTIVESUBWIN->setAlign(Qt::AlignCenter);
    ui->actionAlignment->trigger();
}//on_actionAlCentr_triggered()

void MainWindow::on_actionAlWidth_triggered()
{
    ui->actionAlignment->setIcon(QIcon(":/icons/alignment.png"));
    ACTIVESUBWIN->setAlign(Qt::AlignJustify);
    ui->actionAlignment->trigger();
}//on_actionAlWidth_triggered()

void MainWindow::on_actionPaste_triggered(bool checked)
{
    ui->actionaddTable->setVisible(checked);
    ui->actionDateTime->setVisible(checked);
}//on_actionPaste_triggered(bool checked)

void MainWindow::on_actionDateTime_triggered()
{
    MyTimeDateDialog *dialog = new MyTimeDateDialog (this);
    if (dialog->exec() == QDialog::Accepted) {
        QDateTime data = dialog->getData();
        ACTIVESUBWIN->insertDateTime(data);
    }//if (dialog->exec() == QDialog::Accepted)
    delete dialog;
}//on_actionDateTime_triggered()
