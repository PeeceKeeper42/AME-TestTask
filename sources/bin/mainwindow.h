#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//==============================================================================
#include <QMainWindow>

//==============================================================================
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
//==============================================================================
class ImageViewer;
class DataSorter;
class VideoPlayer;

//==============================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString prjName = QString(),
                        QString authorName = QString(),
                        QString authorLink = QString(),
                        QString prjLink = QString(),
                        QString buildDate = QString(),
                        QWidget *parent = nullptr);
    ~MainWindow();

    void initialize();

private:
    Ui::MainWindow *ui;

    QString m_prjName;
    QString m_authorName;
    QString m_authorLink;
    QString m_prjLink;
    QString m_buildDate;

private slots:
    void showAboutMeWindow(bool isChecked);
};
//==============================================================================
#endif // MAINWINDOW_H
