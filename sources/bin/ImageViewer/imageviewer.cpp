#include "imageviewer.h"
#include "ui_imageviewer.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>

#include <QDebug>

//==============================================================================
ImageViewer::ImageViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);

    initialize();

    createConnections();
}
//==============================================================================
ImageViewer::~ImageViewer()
{
    delete ui;
}
//==============================================================================
void ImageViewer::initialize()
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->gv->setScene(scene);
    ui->gv->installEventFilter(this);

    m_currentScale = 1.0;
    m_pictureLoaded = false;
    setMode(Mode_None);

    ui->le->clear();
}
//==============================================================================
void ImageViewer::createConnections()
{
    connect(ui->btnLoadImage,&QPushButton::clicked, this, &ImageViewer::onBtnLoadImage);

    connect(ui->btnCreatePolygonCancel,&QPushButton::clicked, this, &ImageViewer::onBtnCreatePolygonCancel);
    connect(ui->btnCreatePolygon,&QPushButton::clicked, this, &ImageViewer::onBtnCreatePolygon);
    connect(ui->btnEditPolygon,&QPushButton::clicked, this, &ImageViewer::onBtnEditPolygon);
    connect(ui->btnEditPolygonCancel,&QPushButton::clicked, this, &ImageViewer::onBtnEditPolygonCancel);
}
//==============================================================================
void ImageViewer::updateUi()
{
    ui->btnCreatePolygon->setEnabled(m_currentMode == Mode_None && m_pictureLoaded);
    ui->btnCreatePolygonCancel->setEnabled(m_currentMode == Mode_Creating && m_pictureLoaded);
    ui->btnEditPolygon->setEnabled(m_currentMode == Mode_None && m_pictureLoaded);
    ui->btnEditPolygonCancel->setEnabled(m_currentMode == Mode_Editing && m_pictureLoaded);
}
//==============================================================================
void ImageViewer::onBtnLoadImage()
{
    m_pictureLoaded = false;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Загрузить изображение"),
                                                    "",
                                                    tr("Images (*.png *.jpg *.bmp)"));

    if( fileName.isEmpty() ) return;

    QImage image(fileName);

    if ( image.isNull() ) return;

    ui->gv->scene()->clear();
    ui->le->clear();

    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    ui->gv->scene()->addItem(pixmapItem);
    ui->gv->fitInView(pixmapItem, Qt::KeepAspectRatio);

    m_currentScale = 1.00;
    m_pictureLoaded = true;
    setMode(Mode_None);
}
//==============================================================================
// Конечно можно было просто лямбды использовать, но ожидалась доп логика.
void ImageViewer::onBtnCreatePolygon() { setMode(Mode_Creating); }
//==============================================================================
void ImageViewer::onBtnCreatePolygonCancel() { setMode(Mode_None); }
//==============================================================================
void ImageViewer::onBtnEditPolygon() { setMode(Mode_Editing); }
//==============================================================================
void ImageViewer::onBtnEditPolygonCancel() { setMode(Mode_None); }
//==============================================================================
bool ImageViewer::eventFilter(QObject *obj, QEvent *event)
{
    if(eventDragFilter(obj,event)) return true;
    if(eventCreateFilter(obj,event)) return true;
    if(eventEditFilter(obj,event)) return true;

    return QObject::eventFilter(obj, event);
}
//==============================================================================
bool ImageViewer::eventDragFilter(QObject *obj, QEvent *event)
{
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

    if(obj != ui->gv) return false;

    if (event->type() == QEvent::MouseButtonPress)
    {
        if (mouseEvent->button() == Qt::LeftButton &&
            QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            ui->gv->setDragMode(QGraphicsView::ScrollHandDrag);
            setMode(Mode_Draging);
            return true;
        }
    }
    else if (event->type() == QEvent::MouseMove &&
             m_currentMode == Mode_Draging)
    {
        if (!mouseEvent->button() == Qt::LeftButton ||
            !QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
            ui->gv->setDragMode(QGraphicsView::NoDrag);
            setMode(Mode_None);
            return true;
        }
        return true;
    }
    else if (event->type() == QEvent::MouseButtonRelease)
    {
        if (mouseEvent->button() == Qt::LeftButton)
        {
            ui->gv->setDragMode(QGraphicsView::NoDrag);
            setMode(Mode_None);
            return true;
        }
    }
    else if (event->type() == QEvent::KeyRelease)
    {
        if (keyEvent->key() == Qt::Key_Control &&
            m_currentMode == Mode_Draging)
        {
            ui->gv->setDragMode(QGraphicsView::NoDrag);
            setMode(Mode_None);
            return true;
        }
    }

    showMode();
    return false;
}
//==============================================================================
bool ImageViewer::eventCreateFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)
    Q_UNUSED(event)

    return false;
}
//==============================================================================
bool ImageViewer::eventEditFilter(QObject *obj, QEvent *event)
{
    Q_UNUSED(obj)
    Q_UNUSED(event)

    return false;
}
//==============================================================================
void ImageViewer::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
    {
        m_currentScale *= scaleMultiplier;
        ui->gv->scale(scaleMultiplier, scaleMultiplier);
    }
    else
    {
        m_currentScale /= scaleMultiplier;
        ui->gv->scale(1.0 / scaleMultiplier, 1.0 / scaleMultiplier);
    }
}
//==============================================================================
void ImageViewer::showMode()
{
    QString modeStr;

    switch(m_currentMode)
    {
        case Mode_None: { modeStr = "Ничего не происходит"; break; }
        case Mode_Draging: { modeStr = "Навигация по изображению"; break; }
        case Mode_Creating: { modeStr = "Создание полигона"; break; }
        case Mode_Editing: { modeStr = "Изменение полигона"; break; }
        default: { modeStr = "Неизвестное состояние"; break; }
    }

    ui->le->setText(modeStr);
}
//==============================================================================
void ImageViewer::setMode(ImageViewerMode mode)
{
    m_currentMode = mode;
    showMode();
    updateUi();
}
//==============================================================================
