#include <QScrollBar>
#include "wheelevent.h"

WheelEvent::WheelEvent(QWidget *parent): QGraphicsView(parent) {
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
    if (transform().m11() <= minimalScale){
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

void WheelEvent::setMinimalScale(qreal scale) {
    minimalScale = scale;
    currentScale = scale;

}


