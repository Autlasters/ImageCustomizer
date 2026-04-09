#ifndef WHEELEVENT_H
#define WHEELEVENT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>

class WheelEvent: public QGraphicsView {
    Q_OBJECT
private:
    qreal minimalScale;
    qreal currentScale;
    QPoint lastPosition;
    bool allowMoving = false;
    QGraphicsScene *scene = nullptr;
protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;
public:
    explicit WheelEvent(QWidget *parent = nullptr);
    void setMinimalScale();
    void setImage(const QImage& image);
    void clearScene();
};

#endif // WHEELEVENT_H
