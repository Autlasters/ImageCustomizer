/*
 * filterscollector.cpp
 *
 * This source file implements the logic of the methods of the class FiltersCollector
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include "filterscollector.h"

//Method to get all default filters names
QStringList FiltersCollector::getAllDefaultFilters() {
    return {"Black&White", "Blur", "Bright", "Warm", "Cold", "Sharp", "Sepia", "Edge Detection", "Negative", "Pencil Sketch"};
}

//Method to get all resizing filters names
QStringList FiltersCollector::getAllResizingFilters() {
    return {"640x480", "800x600", "1024x768", "1280x720", "1366x768", "1600x900", "1920x1080", "2560x1440", "3840x2160"};
}

//Method to get all color spaces filters names
QStringList FiltersCollector::getAllColorSpaceFilters() {
    return {"LAB", "YCrCb", "HSV"};
}
