#ifndef WHEELEVENT_H
#define WHEELEVENT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMouseEvent>

class WheelEvent: public QGraphicsView {
    Q_OBJECT
private:
    qreal minimalScale;
    qreal currentScale;
    bool allowMoving = false;
    QPoint lastPosition;
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
public:
    explicit WheelEvent(QWidget *parent = nullptr);
    void setMinimalScale(qreal scale);
};

#endif // WHEELEVENT_H
