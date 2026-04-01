#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QDialog>

namespace Ui { class SaveImage; }

class SaveImage : public QDialog {
    Q_OBJECT
private:
    Ui::SaveImage *ui;
public:
    explicit SaveImage(QWidget *parent = nullptr);
    void setSaveEnable(const QString& name);
    ~SaveImage();
public slots:
    void callSave();
    void callCancel();
signals:
    void saveConfirmed(const QString name);
    void saveCanceled();
};

#endif // SAVEIMAGE_H
