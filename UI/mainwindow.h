#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "opencv2/core/core.hpp"

#include "imagemanager.h"
#include "imageio.h"
#include "imagehistoryio.h"
#include "imagehistorymanager.h"
#include "displayimage.h"
#include "historywindow.h"
#include "draganddropevent.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void exit();
private:
    Ui::MainWindow *ui;
    ImageManager imageManager;
    ImageHistoryManager imageHistoryManager;
    ImageIO userImageIO;
    ImageIO histroyImageIO;
    ImageHistoryIO historyFileIO;
    CustomView *dragAndDropEvent = nullptr;
    DisplayImage *displayWindow = nullptr;
    HistoryWindow *historyWindow = nullptr;
public slots:
    void callSearch();
    void callHistoryWindow();
    void callExit();
    void callProcess();
    void callClear();
    void imageDropped(const QString& path);
    void saveImage(const QString& name, const QImage& image);
    void showHistory(const QString& path);
    void checkDragAndDrop(const QString& path);
};
#endif // MAINWINDOW_H
