#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    path = new QLineEdit (this);

    qApp->setStyleSheet("QMainWindow {background: #FFFFFF;}");

    ui->toolBar->addAction(ui->actionBack);
    ui->toolBar->addAction(ui->actionForward);
    ui->toolBar->addWidget(path);
    ui->toolBar->addAction(ui->actionSearch);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionView);
    ui->toolBar->addAction(ui->actionDayNight);
    ui->toolBar->addAction(ui->actionSettings);
    ui->toolBar->addAction(ui->actionFullScreen);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionAbout);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionExit);

    model = new QFileSystemModel (this);
    model->setFilter(QDir::AllEntries | QDir::NoDot);
    model->setRootPath("/home");

    favour = new QStandardItemModel (this);
    favour->appendRow(new QStandardItem(QIcon(":/icons/home.png"),      tr("Домашняя папка"))); //1
    favour->appendRow(new QStandardItem(QIcon(":/icons/desktop.png"),   tr("Рабочий стол")));   //2
    favour->appendRow(new QStandardItem(QIcon(":/icons/video.png"),     tr("Видео")));          //3
    favour->appendRow(new QStandardItem(QIcon(":/icons/documents.png"), tr("Документы")));      //4
    favour->appendRow(new QStandardItem(QIcon(":/icons/download.png"),  tr("Загрузки")));       //5
    favour->appendRow(new QStandardItem(QIcon(":/icons/images.png"),    tr("Изображения")));    //6
    favour->appendRow(new QStandardItem(QIcon(":/icons/music.png"),     tr("Музыка")));         //7
    favour->appendRow(new QStandardItem(QIcon(":/icons/basket.png"),    tr("Корзина")));        //8

    ui->favour->setModel(favour);
    ui->favour->setIconSize(QSize(24, 24));
    ui->favour->setGridSize(QSize(170, 30));
    ui->favour->setRootIndex(model->index(QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first()));

    ui->device->setIconSize(QSize(24, 24));
    ui->device->setGridSize(QSize(170, 30));
    ui->device->hide();

    ui->user_favour->setIconSize(QSize(24, 24));
    ui->user_favour->setGridSize(QSize(170, 30));

    ui->listView->setModel(model);
    ui->listView->setRootIndex(model->index("/home"));
    ui->listView->setResizeMode(QListView::Adjust);
    ui->listView->setIconSize(QSize(46, 46));
    ui->listView->setGridSize(QSize(100, 70));
    ui->listView->setDragDropMode(QAbstractItemView::NoDragDrop);

    path->setText(model->rootPath());
    connect(path, SIGNAL(returnPressed()), this, SLOT(on_path_returnPressed()));

    timer = new QTimer(this);
    timer->start(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer()));
}//MainWindow(QWidget *parent = nullptr)

#define PATH(P) QStandardPaths::standardLocations(P).first()
#define HOME_PATH QStandardPaths::HomeLocation
#define DESK_PATH QStandardPaths::DesktopLocation
#define VIDE_PATH QStandardPaths::MoviesLocation
#define DOCU_PATH QStandardPaths::DocumentsLocation
#define DOWN_PATH QStandardPaths::DownloadLocation
#define IMAG_PATH QStandardPaths::PicturesLocation
#define MUSI_PATH QStandardPaths::MusicLocation
#define BASK_PATH QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first()

void MainWindow::pushChanges(QStack<QString> &st, QString ch)
{
    if (st.count() == STACK_MAX_SIZE) st.pop_front();
    st.push(ch);
}

inline QStandardPaths::StandardLocation MainWindow::favourDirTransform(int dir)
{
    switch (dir) {
    case HOME:      return HOME_PATH;
    case DESKTOP:   return DESK_PATH;
    case VIDEO:     return VIDE_PATH;
    case DOCUMENTS: return DOCU_PATH;
    case DOWNLOAD:  return DOWN_PATH;
    case IMAGES:    return IMAG_PATH;
    case MUSIC:     return MUSI_PATH;
    default:        return HOME_PATH;
    }//switch (dir)
}//void pushChanges(QStack<QString> &st, QString &ch)

MainWindow::~MainWindow()
{
    delete ui;
}//~MainWindow()

void MainWindow::on_actionFullScreen_triggered()
{
    if (isFullScreen()) {
        showNormal();
        ui->actionFullScreen->setIcon(QIcon(":/icons/fullScreen.png"));
    } else {
        showFullScreen();
        ui->actionFullScreen->setIcon(QIcon(":/icons/fullScreenOff.png"));
    }//if (isFullScreen())
}//on_actionFullScreen_triggered()

void MainWindow::on_actionExit_triggered()
{
    close();
}//on_actionExit_triggered()

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QFileInfo info = model->fileInfo(index);
    if (info.isDir()) {
        if (info.fileName() == "..") {
            QDir d = info.dir();
            d.cdUp();
            ui->listView->setRootIndex(model->index(d.absolutePath()));
        } else ui->listView->setRootIndex(index);
        path->setText(info.absoluteFilePath());
        pushChanges(back, info.path());
    }//if (info.isDir())
}//on_listView_doubleClicked(const QModelIndex &index)

void MainWindow::on_path_returnPressed()
{
    ui->listView->setRootIndex(model->index(path->text()));
}//on_path_returnPressed()

void MainWindow::on_actionView_triggered()
{
    if (ui->listView->viewMode() == QListView::ViewMode::IconMode) {
        ui->listView->setViewMode(QListView::ViewMode::ListMode);
        ui->actionView->setIcon(QIcon(":/icons/list.png"));
    } else {
        ui->listView->setViewMode(QListView::ViewMode::IconMode);
        ui->actionView->setIcon(QIcon(":/icons/icons2.png"));
    }//if (ui->listView->viewMode() == QListView::ViewMode::IconMode)
}//on_actionView_triggered()

void MainWindow::on_actionBack_triggered()
{
    if (back.count()) {
        ui->listView->setRootIndex(model->index(back.top()));
        path->setText(model->fileInfo(model->index(back.top())).absoluteFilePath());
        pushChanges(forvard, back.pop());
    }//if (back.count())
}//on_actionBack_triggered()

void MainWindow::on_actionForward_triggered()
{
    if (forvard.count()) {
        ui->listView->setRootIndex(model->index(forvard.top()));
        path->setText(model->fileInfo(model->index(forvard.top())).absoluteFilePath());
        pushChanges(back, forvard.pop());
    }//if (forvard.count())
}//on_actionForward_triggered()

void MainWindow::on_actionAbout_triggered()
{
    QFile file(":/about.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "О программе", file.readAll());
        file.close();
    }//if (file.open(QIODevice::ReadOnly | QIODevice::Text))
}//on_actionAbout_triggered()

void MainWindow::on_favour_clicked(const QModelIndex &index)
{
    on_listView_doubleClicked(model->index(PATH(favourDirTransform(index.row()))));
}//on_favour_clicked(const QModelIndex &index)

void MainWindow::on_timer()
{
    QList<QStorageInfo> list = QStorageInfo::mountedVolumes();
    QStandardItemModel *m = new QStandardItemModel (this);

    int16_t count = 0;
    QStringList device_names;
    device_names.clear();

    for (auto i : list)
        if (i.name() != "") {
            m->appendRow(new QStandardItem(QIcon(":/icons/device.png"), i.name()));
            device_names << i.name();
            count++;
        }//if (i.name() != "")

    if (count && (device_count != count)) {
        thread = new MyThreadUpdater(device_names, &device_path, this);
        thread->start();
        for (; thread->isRunning(); ) { }
        ui->device->setModel(m);
        ui->device->setMaximumSize(170, count*32);
        ui->device->show();
        device_count = count;
    } else if (!count) ui->device->hide();
}//void on_timer()

void MainWindow::on_user_favour_clicked(const QModelIndex &index)
{

}//on_user_favour_clicked(const QModelIndex &index)

void MainWindow::on_device_clicked(const QModelIndex &index)
{
    on_listView_doubleClicked(model->index(device_path.at(index.row())));
}//on_device_clicked(const QModelIndex &index)
