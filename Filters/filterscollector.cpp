#include "filterscollector.h"

QStringList FiltersCollector::getAllDefaultFilters() {
    return {"Black and White", "Blur", "Bright", "Warm", "Cold", "Sharp", "Sepia", "Edge Detection", "Negative", "Pencil Sketch"};
}

QStringList FiltersCollector::getAllResizingFilters() {
    return {"640x480", "800x600", "1024x768", "1280x720", "1366x768", "1600x900", "1920x1080", "2560x1440", "3840x2160"};
}
