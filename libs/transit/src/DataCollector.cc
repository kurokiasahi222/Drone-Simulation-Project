#include "DataCollector.h"


void DataCollector::addData(std::vector<std::string> newData){}

void DataCollector::toCSV(std::string fileName){}

DataCollector* DataCollector::instance = nullptr;

DataCollector* DataCollector::getInstance(){
    if (instance == nullptr){
        instance = new DataCollector();
    }
    return instance;
}
