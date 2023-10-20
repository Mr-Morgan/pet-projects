#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m = new QStandardItemModel(this);
    ui->tableView->setModel(m);

    ui->toolBar->addAction(ui->actionAdd);
    ui->toolBar->addAction(ui->actionEdit);
    ui->toolBar->addAction(ui->actionDelete);
    ui->toolBar->addAction(ui->actionSave);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionAbout);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionExit);

    QList<QStandardItem*> row;
    row.append(new QStandardItem("Имя программы"));
    row.append(new QStandardItem("Расположение"));

    for (QStandardItem *i : row)
        i->setFlags(Qt::ItemFlag::NoItemFlags);
    m->appendRow(row);
    row.clear();

    QFile file("settings.set");
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        setModelData(stream);
        file.close();
    }//if (file.open(..))
    ui->tableView->resizeColumnsToContents();
}//MainWindow(QWidget *parent = nullptr)

void MainWindow::saveModelData(QTextStream &s)
{
    for (int32_t i = 1; i < m->rowCount(); ++i)
        for (int32_t j = 0; j < m->columnCount(); ++j)
            s << m->itemFromIndex(m->index(i,j))->text() << '\n';
}//void saveModelData(QTextStream &s)

void MainWindow::setModelData(QTextStream &s)
{
    QList<QStandardItem*> row;
    for (; !s.atEnd();) {
        QString str = s.readLine();
        QStandardItem* item = new QStandardItem(str);
        row.append(item);

        str = s.readLine();
        item = new QStandardItem(str);
        row.append(item);

        for (QStandardItem *i : row)
            i->setFlags(Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled);
        m->appendRow(row);
        row.clear();
    }//for (; s.atEnd();)
}//void setModelData(QTextStream &s)

MainWindow::~MainWindow()
{
    delete ui;
}//~MainWindow()

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case 0x01000031:
        if (m->rowCount() >= 1) on_tableView_doubleClicked(m->index(1,1));
        break;
    case Qt::Key_F3:
        if (m->rowCount() >= 2) on_tableView_doubleClicked(m->index(2,1));
        break;
    case Qt::Key_F4:
        if (m->rowCount() >= 3) on_tableView_doubleClicked(m->index(3,1));
        break;
    case Qt::Key_F5:
        if (m->rowCount() >= 4) on_tableView_doubleClicked(m->index(4,1));
        break;
    case Qt::Key_F6:
        if (m->rowCount() >= 5) on_tableView_doubleClicked(m->index(5,1));
        break;
    case Qt::Key_F7:
        if (m->rowCount() >= 6) on_tableView_doubleClicked(m->index(6,1));
        break;
    case Qt::Key_F8:
        if (m->rowCount() >= 7) on_tableView_doubleClicked(m->index(7,1));
        break;
    case Qt::Key_F9:
        if (m->rowCount() >= 8) on_tableView_doubleClicked(m->index(8,1));
        break;
    case Qt::Key_F10:
        if (m->rowCount() >= 9) on_tableView_doubleClicked(m->index(9,1));
        break;
    default:
        break;
    }//switch (e->key())
}//void keyReleaseEvent(QKeyEvent *e) override

void MainWindow::on_actionAdd_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Выберите исполняемый файл для добавления",
                                                    QDir::current().path(), QString("Все файлы(*)"));
    if (filename.length()) {
        QList<QStandardItem*> row;
        QStandardItem* item = new QStandardItem(filename.right(filename.length() - filename.lastIndexOf('/') - 1));
        row.append(item);
        item = new QStandardItem(filename);
        row.append(item);
        for (QStandardItem *i : row)
            i->setFlags(Qt::ItemFlag::ItemIsSelectable | Qt::ItemFlag::ItemIsEnabled);
        m->appendRow(row);
        ui->tableView->resizeColumnsToContents();
        row.clear();
    }//if (filename.length())
}//on_actionAdd_triggered()

void MainWindow::on_actionDelete_triggered()
{
    m->removeRow(ui->tableView->currentIndex().row());
}//on_actionDelete_triggered()

void MainWindow::on_actionAbout_triggered()
{
    QFile file(":/about.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "О программе", file.readAll());
        file.close();
    }//if (file.open(QIODevice::ReadOnly | QIODevice::Text))
}//on_actionAbout_triggered()

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QProcess proc(this);
    QString name = m->itemFromIndex(m->index(index.row(),1))->text();
    proc.startDetached(name);
}//on_tableView_doubleClicked(const QModelIndex &index);

void MainWindow::on_actionExit_triggered()
{
    close();
}//on_actionExit_triggered()

void MainWindow::on_actionEdit_triggered(bool checked)
{
    if (checked)
        for (int i = 0; i < m->rowCount(); ++i)
            m->itemFromIndex(m->index(i,0))->
                    setFlags(m->itemFromIndex(m->index(i,0))->flags() | Qt::ItemFlag::ItemIsEditable);
    else
        for (int i = 0; i < m->rowCount(); ++i)
            m->itemFromIndex(m->index(i,0))->
                    setFlags(m->itemFromIndex(m->index(i,0))->flags() ^ Qt::ItemFlag::ItemIsEditable);
}//on_actionEdit_triggered(bool checked)

void MainWindow::on_actionSave_triggered()
{
    QFile file("settings.set");
    if (file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        saveModelData(stream);
        file.close();
    }//if (file.open(..))
}//on_actionSave_triggered()
