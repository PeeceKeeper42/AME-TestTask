#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#include "ImageViewer/imageviewer.h"
#include "DataSorter/datasorter.h"
#include "VideoPlayer/videoplayer.h"

//==============================================================================
MainWindow::MainWindow( QString prjName, QString authorName, QString authorLink,
                        QString prjLink, QString buildDate, QWidget *parent) :
    m_prjName(prjName), m_authorName(authorName), m_authorLink(authorLink),
    m_prjLink(prjLink), m_buildDate(buildDate), QMainWindow(parent),
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

    QAction* aboutMeAction = new QAction(tr("О программе"), this);
    aboutMeAction->setObjectName("AboutMeAction");
    aboutMeAction->setIcon(QIcon(":/icons/about.png"));
    aboutMeAction->setStatusTip(tr("Информация о программе"));

    ui->menubar->clear();
    ui->menubar->setLayoutDirection(Qt::RightToLeft);
    ui->menubar->addAction(aboutMeAction);

    connect(aboutMeAction, &QAction::triggered, this, &MainWindow::showAboutMeWindow);
}
//==============================================================================

//==============================================================================

//==============================================================================
void MainWindow::showAboutMeWindow(bool isChecked)
{
    Q_UNUSED(isChecked)

    QMessageBox* messageBox = new QMessageBox(this);
    messageBox->setObjectName("AboutMeWindow");
    messageBox->setAttribute(Qt::WA_DeleteOnClose);
    messageBox->setFixedSize(460, 670);
    messageBox->setWindowTitle(tr("О программе"));
    messageBox->setTextFormat(Qt::MarkdownText);

    QString aboutMeTitleString = tr("### Тестовое задание для АО НПП «Авиационная и морская электроника» \n\n");
    QString aboutMeString = tr(
                               "Наименование проекта (CMake): %1 \n"
                               "Никнейм автора (Git): %2 \n"
                               "Ссылка на страницу автора: %3 \n"
                               "Ссылка на страницу проекта: %4 \n"
                               "Дата сборки проекта: %5")
                                .arg(m_prjName)
                                .arg(m_authorName)
                                .arg(m_authorLink)
                                .arg(m_prjLink)
                                .arg(m_buildDate);


    messageBox->setText(aboutMeTitleString);
    messageBox->setInformativeText(aboutMeString);
    messageBox->show();
}
//==============================================================================
