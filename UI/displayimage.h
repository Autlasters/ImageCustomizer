#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QDialog>
#include <QImage>
#include <QGraphicsScene>

namespace Ui {
class DisplayImage;
}

class DisplayImage : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayImage(QWidget *parent = nullptr);
    void setImage(const QImage& image);
    void resizeEvent(QResizeEvent * event);
    void showEvent(QShowEvent *event);
    void setSaveEnable(bool permission);
    ~DisplayImage();

private:
    Ui::DisplayImage *ui;
    QImage image;
    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *pixmapItem = nullptr;
public slots:
    void callSave();
    void callClose(); 
signals:
    void saveRequest(const QString& name, const QImage& image);
};

#endif // DISPLAYIMAGE_H
