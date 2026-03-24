#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QDialog>

namespace Ui {
class DisplayImage;
}

class DisplayImage : public QDialog
{
    Q_OBJECT

public:
    explicit DisplayImage(QWidget *parent = nullptr);
    ~DisplayImage();

private:
    Ui::DisplayImage *ui;
public slots:
    void callSave();
    void callClose();
};

#endif // DISPLAYIMAGE_H
