#ifndef FILTERSCOLLECTOR_H
#define FILTERSCOLLECTOR_H

#include <QStringList>

class FiltersCollector {
public:
    static QStringList getAllDefaultFilters();
    static QStringList getAllResizingFilters();
};

#endif // FILTERSCOLLECTOR_H
