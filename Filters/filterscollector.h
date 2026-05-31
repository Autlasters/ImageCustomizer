/*
 * filterscollector.h
 *
 * This header file represents the FiltersCollector class, which is responsible for giving the filters names for the UI dropdowns
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#ifndef FILTERSCOLLECTOR_H
#define FILTERSCOLLECTOR_H

#include <QStringList>

class FiltersCollector {
public:
    static QStringList getAllDefaultFilters();
    static QStringList getAllResizingFilters();
    static QStringList getAllColorSpaceFilters();
};

#endif // FILTERSCOLLECTOR_H
