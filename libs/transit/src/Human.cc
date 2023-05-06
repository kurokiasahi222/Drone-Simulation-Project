#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"

Human::Human(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
}

Human::~Human() {
  // Delete dynamically allocated variables
  delete graph;
}

void Human::CreateNewDestination() {
    destination = {Random(-1400, 1500), position.y, Random(-800, 800)};
    toDestination = new AstarStrategy(position, destination, graph);

    // notification: heading to destination
    std::string notif = details["name"].ToString()
                        + " is on the way to {"
                        + std::to_string(destination.x).substr(0,
                            std::to_string(destination.x).size()-4)
                        + ", " + std::to_string(destination.y).substr(0,
                            std::to_string(destination.y).size()-4)
                        + ", " + std::to_string(destination.z).substr(0,
                            std::to_string(destination.z).size()-4)
                        +"}";
    Notify(notif);
}

void Human::Update(double dt, std::vector<IEntity*> scheduler) {
    if (toDestination) {
        if (toDestination->IsCompleted()) {
            // notification: arrived at destination
            std::string notif = details["name"].ToString()
                                + " has arrived, generating new destination";
            Notify(notif);

            CreateNewDestination();
        } else {
            toDestination->Move(this, dt);
        }
    } else {
        CreateNewDestination();
    }
}
