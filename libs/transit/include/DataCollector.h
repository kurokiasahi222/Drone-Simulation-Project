#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H

#include <string>
#include <vector>

class DataCollector {
    public:
        //It's what makes a singleton, a singleton
        static DataCollector* getInstance();

        //Can change input parameters if needed
        void addData(std::vector<std::string> newData);

        void toCSV(std::string fileName);

        //No copying
        DataCollector(DataCollector &other) = delete;

        void operator=(const DataCollector &) = delete;

        //For debugging-possibly change to print
        std::vector<std::vector<std::string>> getData(){return data;}

    private:
        DataCollector(){};
        static DataCollector* instance;
        std::vector<std::vector<std::string>> data;
};

DataCollector* instance = nullptr;

DataCollector* DataCollector::getInstance(){
    if (instance == nullptr){
        instance = new DataCollector();
    }
    return instance;
}
#endif