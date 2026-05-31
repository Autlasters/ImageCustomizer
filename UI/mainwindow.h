/*
 * mainwindow.h
 *
 * This header file represents the MainWindow class, which is responsible for showing the main window of the application
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
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
    enum Mode {DefaultMode, ResizingMode, ColorSpacesMode};
    Ui::MainWindow *ui;
    CustomView *view = nullptr;
    DisplayImage *displayWindow = nullptr;
    ImageManager imageManager;
    ImageIO userImageIO;
    QSettings settings;
    bool imagesLoaded = false;
    Mode mode;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void callSearch();
    void callProcess();
    void callClear();
    void callClose();
    void imageDropped(const QString& path);
    void saveImage(const QString& name, const QString& extension, const QImage& image);
    void changeButtonsState();
    void fillFiltersDropdown();
    void fillModeDropDown();
    void changeMode();
signals:
    void filtersModeChanged();
};

#endif // MAINWINDOW_H
