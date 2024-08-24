#include <QApplication>
#include <QtCore>
#include <QDebug>

#include "config.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    qDebug() << CMAKE_PROJECT_NAME;
    qDebug() << GIT_AUTHOR;
    qDebug() << GIT_AUTHOR_LINK;
    qDebug() << GIT_PROJECT_LINK;
    qDebug() << BUILD_DATE;

    MainWindow w;
    w.setObjectName("MainWindow");
    w.show();
    return a.exec();
}
