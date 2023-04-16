#include "Observer.h"

 void Observer::Update(const std::string &message) {
  JsonObject details;
  details["message"] = message;
  controller_->SendEventToView("DisplayNotification", details);
 };