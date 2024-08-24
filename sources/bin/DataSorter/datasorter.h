#ifndef DATASORTER_H
#define DATASORTER_H
//==============================================================================
#include <QWidget>

//==============================================================================
namespace Ui {
class DataSorter;
}
//==============================================================================
class DataSorter : public QWidget
{
    Q_OBJECT

public:
    explicit DataSorter(QWidget *parent = nullptr);
    ~DataSorter();

private:
    Ui::DataSorter *ui;
};
//==============================================================================
#endif // DATASORTER_H
