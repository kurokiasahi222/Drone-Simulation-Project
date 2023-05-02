#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "DataCollector.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }

  if (nearestEntity) {
      // set availability to the nearest entity
    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;
    hasNotifiedTraveling = false;

    // notification: heading to pick up RobotX
    std::string notif = details["name"].ToString()
                        + " is on the way to pick up "
                        + nearestEntity->GetDetails()["name"].ToString();
    Notify(notif);

    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination();

    toRobot = new BeelineStrategy(position, destination);

    std::string strat = nearestEntity->GetStrategyName();
    if (strat == "astar")
      toFinalDestination =
        new JumpDecorator(new AstarStrategy(
                          destination, finalDestination, graph));

    else if (strat == "dfs")
      toFinalDestination =
        new SpinDecorator(new JumpDecorator(
                          new DfsStrategy(
                          destination, finalDestination, graph)));

    else if (strat == "dijkstra")
      toFinalDestination =
        new JumpDecorator(new SpinDecorator(
                          new DijkstraStrategy(
                          destination, finalDestination, graph)));

    else
      toFinalDestination = new BeelineStrategy(destination, finalDestination);
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  totalTime += dt;
  timeSinceUpdate += dt;
  if (available)
    GetNearestEntity(scheduler);

  if (toRobot) {
    toRobot->Move(this, dt);

    if (toRobot->IsCompleted()) {
      // notification: picked up RobotX
      std::string notif = details["name"].ToString()
                          + " has picked up "
                          + nearestEntity->GetDetails()["name"].ToString();
      Notify(notif);

      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
    }
  } else if (toFinalDestination) {
    // notification: travelling to final destination
    if (!hasNotifiedTraveling) {
      std::string notif = details["name"].ToString() + " is delivering "
                          + nearestEntity->GetDetails()["name"].ToString()
                          + " using " + nearestEntity->GetStrategyName()
                          + " strategy";
      Notify(notif);
      hasNotifiedTraveling = true;
    }

    toFinalDestination->Move(this, dt);

    if (nearestEntity && pickedUp) {
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      // notification: dropped off robotX
      std::string notif = details["name"].ToString() + " has dropped off "
                          + nearestEntity->GetDetails()["name"].ToString();
      Notify(notif);
      nearestEntity->SetDelivered(true);

      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      pickedUp = false;
    }
  }
  ReportData();
}

void Drone::ReportData() {
  if (timeSinceUpdate > 0.5) {
    DataCollector* collector = DataCollector::getInstance();
    // Get's data
    std::vector<std::string> data = {};
    data.push_back(details["type"]);
    data.push_back(std::to_string(id));
    data.push_back(position.toString());
    data.push_back(destination.toString());
    data.push_back(std::to_string(speed));
    data.push_back(available ? "1" : "0");
    data.push_back(pickedUp ? "1" : "0");
    data.push_back("N/A");
    data.push_back("N/A");
    data.push_back(std::to_string(totalTime));
    collector->addData(data);
    timeSinceUpdate = 0;
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}



