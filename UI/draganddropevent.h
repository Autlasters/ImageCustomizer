/*
 * draganddropevent.h
 *
 * This header file represents the CustomView class, which is responsible for the drag&drop event in the MainWindow
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

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
    void clearScene();
    void showPlaceHolder();
signals:
    void imageDropped(const QString& path);
};

#endif // DRAGANDDROPEVENT_H
