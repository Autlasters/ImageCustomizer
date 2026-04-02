#ifndef DRAGANDDROPEVENT_H
#define DRAGANDDROPEVENT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QWidget>
#include <QMimeData>
#include <QGraphicsPixmapItem>

class CustomView: public QGraphicsView {
    Q_OBJECT
protected:
    QGraphicsScene *scene = nullptr;
public:
    explicit CustomView(QWidget *parent = nullptr);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    QGraphicsScene *getScene() const;
    void clearScene();
    void showPlaceHolder();
signals:
    void imageDropped(const QString& path);
};

#endif // DRAGANDDROPEVENT_H
