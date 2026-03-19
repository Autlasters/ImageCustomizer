#ifndef FILTERSFACTORY_H
#define FILTERSFACTORY_H

#include <memory>
#include <QString>
#include "filters.h"

class FiltersFactory {
public:
    static std::unique_ptr<Filters> createFilter(const QString& filterName);
};

#endif // FILTERSFACTORY_H
