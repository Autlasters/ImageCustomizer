/*
 * filtersfactory.h
 *
 * This header file represents the FiltersFactory class, which is responsible for creating filters
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#ifndef FILTERSFACTORY_H
#define FILTERSFACTORY_H

#include <memory>
#include <QString>
#include "filters.h"

class FiltersFactory {
public:
    static std::unique_ptr<Filter> createFilter(const QString& filterName);
};

#endif // FILTERSFACTORY_H
