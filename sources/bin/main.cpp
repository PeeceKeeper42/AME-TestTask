#include <QApplication>
#include <QtCore>
#include <QDebug>

#include "config.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    MainWindow w(QString(CMAKE_PROJECT_NAME),
                 QString(GIT_AUTHOR),
                 QString(GIT_AUTHOR_LINK),
                 QString(GIT_PROJECT_LINK),
                 QString(BUILD_DATE));
    w.setObjectName("MainWindow");
    w.show();
    return a.exec();
}
