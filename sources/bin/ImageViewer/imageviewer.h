#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H
//==============================================================================
#include <QWidget>
#include <QGraphicsPolygonItem>

//==============================================================================
namespace Ui {
class ImageViewer;
}
//==============================================================================
enum ImageViewerMode: quint8;
//==============================================================================
class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);
    ~ImageViewer();

private:
    Ui::ImageViewer *ui;
    ImageViewerMode m_currentMode;

    QVector<QPointF> m_polygonPoints;
    QGraphicsPolygonItem *m_currentPolygon;
    QList<QGraphicsPolygonItem*> m_polygons;
    QList<QGraphicsEllipseItem*> m_vertexItems;
    QList<QGraphicsLineItem*> m_edgeItems;

    const qreal scaleMultiplier = 1.15;

    qreal m_currentScale = 1.00;
    bool m_isDragging = false;
    bool m_isCreatingPolygon = false;
    bool m_isEditingPolygon = false;
    bool m_pictureLoaded = false;


    void initialize();
    void createConnections();
    void updateUi();
    void showMode();
    void setMode(ImageViewerMode mode);

    void addPolygonPoint(const QPointF &point);
    void completePolygon();
    void cancelPolygon();

private slots:
    void onBtnLoadImage();

    void onBtnCreatePolygon();
    void onBtnCreatePolygonCancel();
    void onBtnEditPolygon();
    void onBtnEditPolygonCancel();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    bool eventDragFilter(QObject *obj, QEvent *event);
    bool eventCreateFilter(QObject *obj, QEvent *event);
    bool eventEditFilter(QObject *obj, QEvent *event);
};
//==============================================================================
enum ImageViewerMode: quint8
{
    Mode_None       = 0,
    Mode_Draging    = 1,
    Mode_Creating   = 2,
    Mode_Editing    = 3,
};

//==============================================================================
#endif // IMAGEVIEWER_H
