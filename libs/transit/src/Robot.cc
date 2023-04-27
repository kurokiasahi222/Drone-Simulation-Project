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
                            + ", " + std::to_string(position.x).substr(0,
                                std::to_string(position.y).size()-4)
                            + ", " + std::to_string(position.x).substr(0,
                                std::to_string(position.z).size()-4)
                            +"}";
    Notify(notif);
  std::string notif = details["name"].ToString()
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
