#include "draganddropevent.h"

CustomView::CustomView(QWidget *parent): QGraphicsView(parent) {
    setAcceptDrops(true);
    scene = new QGraphicsScene(this);
    setScene(scene);
    viewport()->installEventFilter(this);
    showPlaceHolder();
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
    if(event->source() == this){
        return;
    }
    if(!event->mimeData()->hasUrls()){
        return;
    }
    const QList<QUrl>& urlList = event->mimeData()->urls();
    for(const QUrl& url : urlList){
        if(!url.isLocalFile()){
            continue;
        }
        QString filePath = url.toLocalFile();
        QPixmap img(filePath);
        if(img.isNull()){
            continue;
        }
        scene->clear();
        resetTransform();
        QGraphicsPixmapItem* item = scene->addPixmap(img);
        scene->setSceneRect(item->boundingRect());
        fitInView(item, Qt::KeepAspectRatio);
        event->acceptProposedAction();
        emit imageDropped(filePath);
        break;
    }
}

QGraphicsScene *CustomView::getScene() const {
    return scene;
}

void CustomView::clearScene() {
    if(!scene){
        return;
    }
    scene->clear();
    resetTransform();
    showPlaceHolder();
    scene->setSceneRect(scene->itemsBoundingRect());
    centerOn(scene->sceneRect().center());
    viewport()->update();
}

void CustomView::showPlaceHolder() {
    QGraphicsTextItem *text = scene->addText("Drag&Drop Image Here");
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    text->setFont(font);
    QPoint point = viewport()->rect().center();
    QPointF alignment = mapToScene(point);
    QRectF textRect = text->boundingRect();
    text->setPos(alignment.x() - textRect.width() / 2, alignment.y() - textRect.height() / 2);
    scene->setSceneRect(scene->itemsBoundingRect());
}
