#include "draganddropevent.h"

DragAndDropEvent::DragAndDropEvent() {}

CustomView::CustomView(QWidget *parent): QGraphicsView(parent) {
    setAcceptDrops(true);
    scene = new QGraphicsScene(this);
    setScene(scene);
    viewport()->installEventFilter(this);
}

void CustomView::dragEnterEvent(QDragEnterEvent *event) {
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }
}

void CustomView::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void CustomView::dragMoveEvent(QDragMoveEvent *event) {
    event->accept();
    event->acceptProposedAction();
}

void CustomView::dropEvent(QDropEvent *event) {
    if(event->source() == this) return;
    if(!event->mimeData()->hasUrls()) return;
    const QList<QUrl>& urlList = event->mimeData()->urls();
    for(const QUrl& url : urlList){
        if(!url.isLocalFile()) continue;
        QString filePath = url.toLocalFile();
        QPixmap img(filePath);
        if(img.isNull()) continue;
        scene->clear();
        QGraphicsPixmapItem* item = scene->addPixmap(img);
        scene->setSceneRect(img.rect());
        fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        event->acceptProposedAction();
        emit imageDropped(filePath);
        break;
    }
}
