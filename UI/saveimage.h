#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QDialog>
#include <QStringList>

namespace Ui { class SaveImage; }

class SaveImage : public QDialog {
    Q_OBJECT
private:
    Ui::SaveImage *ui;
public:
    explicit SaveImage(const QStringList& extensions, QWidget *parent = nullptr);
    void setSaveEnable();
    ~SaveImage();
public slots:
    void callSave();
    void callCancel();
signals:
    void saveConfirmed(const QString name, const QString extension);
};

#endif // SAVEIMAGE_H
