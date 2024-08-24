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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initialize();

private:
    Ui::MainWindow *ui;
};
//==============================================================================
#endif // MAINWINDOW_H
