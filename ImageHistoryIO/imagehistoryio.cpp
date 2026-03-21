#include "imagehistoryio.h"

bool ImageHistoryIO::setPath(const QString& path){
    if(path.isEmpty()){
        return false;
    }
    this->path = path;
    return true;
}


bool ImageHistoryIO::saveHistory(const std::vector<ImageHistory>& history) const{
    if(path.isEmpty()){
        return false;
    }

    std::ofstream fileToSave(path.toStdString());
    if(!fileToSave.is_open()){
        return false;
    }

    for(const auto& obj : history){
        fileToSave << obj.getImagePath().toStdString() << "|"
                   << obj.getImageName().toStdString() << "|"
                   << obj.getFiltersHistory().join(",").toStdString() << std::endl;
    }
    fileToSave.close();
    return true;
}

std::vector<ImageHistory> ImageHistoryIO::loadHistory() const{
    std::vector<ImageHistory> temp;
    if(path.isEmpty()){
        return temp;
    }

    std::ifstream fileToLoad(path.toStdString());
    if(!fileToLoad.is_open()){
        return temp;
    }

    std::string lineToRead;
    while(std::getline(fileToLoad, lineToRead)){
        if(lineToRead.empty()){
            continue;
        }
        std::stringstream ss(lineToRead);
        std::string imagePath, imageName, filters;
        if(std::getline(ss, imagePath, '|') && std::getline(ss, imageName, '|') && std::getline(ss, filters, '|')){
            QStringList filtersList = QString::fromStdString(filters).split(',');
            temp.emplace_back(QString::fromStdString(imagePath), QString::fromStdString(imageName), filtersList);
        }
    }
    fileToLoad.close();
    return temp;
}
