/*
 * filtersfactory.cpp
 *
 * This source file implements the logic of the method of the class FiltersFactory
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include "filtersfactory.h"

//Method to create the needed filter
std::unique_ptr<Filter> FiltersFactory::createFilter(const QString& filterName){
    if(filterName == "Black&White"){
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
    if(filterName == "Negative"){
        return std::make_unique<NegativeFilter>();
    }
    if(filterName == "Pencil Sketch"){
        return std::make_unique<PencilSketchFilter>();
    }
    if(filterName == "LAB"){
        return std::make_unique<LABFilter>();
    }
    if(filterName == "YCrCb"){
        return std::make_unique<YCrCbFilter>();
    }
    if(filterName == "HSV"){
        return std::make_unique<HSVFilter>();
    }
    return nullptr;
}
