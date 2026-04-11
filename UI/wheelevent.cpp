#include <QScrollBar>
#include "wheelevent.h"

WheelEvent::WheelEvent(QWidget *parent): QGraphicsView(parent), scene(new QGraphicsScene(this)) {
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void WheelEvent::wheelEvent(QWheelEvent *event){
    setTransformationAnchor(AnchorUnderMouse);
    qreal scaleFactor = 1.5;
    if(event->angleDelta().y() > 0){
        scale(scaleFactor, scaleFactor);
        currentScale *= scaleFactor;
    }
    else{
        qreal newScale = currentScale / scaleFactor;
        if(newScale < minimalScale){
            return;
        }
        scale(1/scaleFactor, 1/scaleFactor);
        currentScale = newScale;
    }
}

void WheelEvent::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        allowMoving = true;
        lastPosition = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void WheelEvent::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        allowMoving = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void WheelEvent::mouseMoveEvent(QMouseEvent *event) {
    if (currentScale <= minimalScale){
        return;
    }
    if(allowMoving){
        QPoint delta = event->pos() - lastPosition;
        lastPosition = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void WheelEvent::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    if(!scene || scene->items().isEmpty()){
        return;
    }
    setMinimalScale();
}

void WheelEvent::showEvent(QShowEvent *event) {
    QGraphicsView::showEvent(event);
    if(!scene || scene->items().isEmpty()){
        return;
    }
    setMinimalScale();
}

void WheelEvent::setMinimalScale() {
    QRectF sceneRect = scene->sceneRect();
    QRectF viewRect = viewport()->rect();
    qreal sx = viewRect.width() / sceneRect.width();
    qreal sy = viewRect.height() / sceneRect.height();
    minimalScale = qMin(sx, sy);
    resetTransform();
    scale(minimalScale, minimalScale);
    currentScale = minimalScale;
}

void WheelEvent::setImage(const QImage &image) {
    QPixmap pixmap = QPixmap::fromImage(image);
    scene->clear();
    QGraphicsPixmapItem *item = scene->addPixmap(pixmap);
    scene->setSceneRect(item->boundingRect());
}

void WheelEvent::clearScene() {
    if(!scene){
        return;
    }
    scene->clear();
    scene->setSceneRect(scene->itemsBoundingRect());
    centerOn(scene->sceneRect().center());
    viewport()->update();
}


