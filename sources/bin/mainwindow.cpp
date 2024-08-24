#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ImageViewer/imageviewer.h"
#include "DataSorter/datasorter.h"
#include "VideoPlayer/videoplayer.h"

//==============================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}
//==============================================================================
MainWindow::~MainWindow()
{

    delete ui;
}
//==============================================================================
void MainWindow::initialize()
{
    while (ui->tabWidget->count() > 0) {

        QWidget *w = ui->tabWidget->widget(0);
        ui->tabWidget->removeTab(0);

        if (w) delete w;
    }

    ImageViewer* imageViewer = new ImageViewer(this);
    imageViewer->setObjectName("ImageViewer");
    ui->tabWidget->addTab( imageViewer, QIcon(":/icons/image.png"), tr("Задание 1") );

    DataSorter* dataSorter = new DataSorter(this);
    dataSorter->setObjectName("DataSorter");
    ui->tabWidget->addTab( dataSorter, QIcon(":/icons/data.png"), tr("Задание 2") );

    VideoPlayer* videoPlayer = new VideoPlayer(this);
    videoPlayer->setObjectName("VideoPlayer");
    ui->tabWidget->addTab( videoPlayer, QIcon(":/icons/videocamera.png"), tr("Задание 3") );
}
//==============================================================================

//==============================================================================

//==============================================================================

//==============================================================================
