#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QDialog>

namespace Ui {
class SaveImage;
}

class SaveImage : public QDialog
{
    Q_OBJECT

public:
    explicit SaveImage(QWidget *parent = nullptr);
    ~SaveImage();

private:
    Ui::SaveImage *ui;
public slots:
    void callSave();
    void callCancel();
signals:
    void saveConfirmed(const QString name);
    void saveCanceled();
};

#endif // SAVEIMAGE_H
