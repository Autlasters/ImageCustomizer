#include "filtersfactory.h"

std::unique_ptr<Filter> FiltersFactory::createFilter(const QString& filterName){
    if(filterName == "Black and White"){
        return std::make_unique<BlackAndWhiteFilter>();
    }
    if(filterName == "Blur"){
        return std::make_unique<BlurFilter>();
    }
    if(filterName == "Bright"){
        return std::make_unique<BrightFilter>();
    }
    if(filterName == "Warm"){
        return std::make_unique<WarmFilter>();
    }
    if(filterName == "Cold"){
        return std::make_unique<ColdFilter>();
    }
    if(filterName == "Sharp"){
        return std::make_unique<SharpFilter>();
    }
    if(filterName == "Sepia"){
        return std::make_unique<SepiaFilter>();
    }
    if(filterName == "Edge Detection"){
        return std::make_unique<EdgeDetectionFilter>();
    }
    return nullptr;
}
