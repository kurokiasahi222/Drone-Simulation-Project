#include "Robot.h"

Robot::Robot(JsonObject &obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};
  speed = obj["speed"];
  available = true;

  // notification: robotX created, waiting to be picked up
  // name from the details
  std::string notif = details["name"].ToString()
                        + " was created at {"
                            + std::to_string(position.x).substr(0,
                                std::to_string(position.x).size()-4)
                            + ", " + std::to_string(position.y).substr(0,
                                std::to_string(position.y).size()-4)
                            + ", " + std::to_string(position.z).substr(0,
                                std::to_string(position.z).size()-4)
                            +"}";
  Notify(notif);
  notif = details["name"].ToString()
    + " is waiting to be picked up";
  Notify(notif);
}

Robot::~Robot() {}

JsonObject Robot::GetDetails() const { return details; }

void Robot::SetAvailability(bool choice) { available = choice; }

void Robot::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Robot::Update(double dt, std::vector<IEntity*> scheduler){
  totalTime += dt;
  timeSinceUpdate += dt;
  ReportData();
}

void Robot::ReportData(){
  //If it is time to update
  if (timeSinceUpdate > 0.5){
    DataCollector* collector = DataCollector::getInstance();
    // Makes string vector of data
    std::vector<std::string> data = {};
    data.push_back(details["type"]);
    data.push_back(std::to_string(id));
    data.push_back(position.toString());
    data.push_back(destination.toString());
    data.push_back(std::to_string(speed));
    data.push_back(available ? "1" : "0");
    data.push_back("N/A");
    data.push_back(delivered ? "1" : "0");
    data.push_back(strategyName);
    data.push_back(std::to_string(totalTime));
    //Reports it to collector
    collector->addData(data);
    timeSinceUpdate = 0;
  }
}
