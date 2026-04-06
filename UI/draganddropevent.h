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
private:
    QGraphicsScene *scene = nullptr;
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
public:
    explicit CustomView(QWidget *parent = nullptr);
    QGraphicsScene *getScene() const;
    void clearScene();
    void showPlaceHolder();
signals:
    void imageDropped(const QString& path);
};

#endif // DRAGANDDROPEVENT_H
