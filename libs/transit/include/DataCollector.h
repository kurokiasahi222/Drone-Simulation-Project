#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H

#include <string>
#include <vector>
#include <ostream>
#include <fstream>

/**
 * @brief this class use singleton pattern to implement a data
 * collector that will be used to collect data from the drone
 */
class DataCollector {
 public:
   /**
   * @brief Gets the the instance of the data collector
   * @return The instance of the data collector
   */
    static DataCollector* getInstance();

   /**
   * @brief Adds data to the data collector
   * @param newData The new data to be added
   */
    void addData(std::vector<std::string> newData);

   /**
   * @brief Writes the data to a csv file
   * @param fileName The name of the file to be written to
   */
    void toCSV(std::string fileName);

    //No copying
    DataCollector(DataCollector &other) = delete;

    void operator=(const DataCollector &) = delete;

    /**
    * @brief Gets the data from the data collector
    * @return The data from the data collector
    */
    std::vector<std::vector<std::string>> getData(){return data;}

 private:
    DataCollector(){};
    static DataCollector* instance;
    std::vector<std::vector<std::string>> data;
};

#endif
