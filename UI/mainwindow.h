#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSettings>
#include "opencv2/core/core.hpp"

#include "imagemanager.h"
#include "imageio.h"
#include "displayimage.h"
#include "draganddropevent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    ImageManager imageManager;
    ImageIO userImageIO;
    ImageIO histroyImageIO;
    CustomView *view = nullptr;
    DisplayImage *displayWindow = nullptr;
    QSettings settings;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void callSearch();
    void callProcess();
    void callClear();
    void callExit();
    void imageDropped(const QString& path);
    void saveImage(const QString& name, const QImage& image);
    void checkDragAndDrop(const QString& path);
};
#endif // MAINWINDOW_H
