#include "DataCollector.h"
#include <iostream>
#include <fstream>

void DataCollector::addData(std::vector<std::string> newData){
    data.push_back(newData);
}
void DataCollector::toCSV(std::string fileName){
    std::ofstream file;
    std::cout << "toCSV called" << std::endl;
    file.open(fileName);
    for (auto row : data){
        for (auto col : row){
            file << col << ",";
        }
        file << std::endl;
    }
    file.close();
}

DataCollector* DataCollector::instance = nullptr;

DataCollector* DataCollector::getInstance(){
    if (instance == nullptr){
        instance = new DataCollector();
    }
    return instance;
}
