#include "Observer.h"

void Observer::Update(const std::string& message) {
  JsonObject details;
  details["info"] = message + "\n";
  controller_.SendEventToView("observe", details);
}
