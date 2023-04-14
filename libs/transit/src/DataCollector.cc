#include "DataCollector.h"


void DataCollector::addData(std::vector<std::string> newData){
    data.push_back(newData);
}
void DataCollector::toCSV(std::string fileName){
    std::ofstream file;
    file.open(fileName);
    for (auto row : data){
        for (auto col : row){
            file << col << ",";
        }
        file << std::endl;
    }
    file.close();
}

