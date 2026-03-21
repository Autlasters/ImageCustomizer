#include "filtersfactory.h"

std::unique_ptr<Filter> FiltersFactory::createFilter(const QString& filterName){
    if(filterName == "BlackAndWhite"){
        return std::make_unique<BlackAndWhiteFilter>();
    }
    if(filterName == "Blur"){
        return std::make_unique<BlurFilter>();
    }
    return nullptr;
}
