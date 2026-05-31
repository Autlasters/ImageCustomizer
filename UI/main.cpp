/*
 * main.cpp
 *
 * This source file to run the application
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w1;
    w1.show();
    return a.exec();
}
