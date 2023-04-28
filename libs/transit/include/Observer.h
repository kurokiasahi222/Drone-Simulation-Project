#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "IObserver.h"
#include "IController.h"

/**
 * @class Observer
 * @brief Concrete observer that subscribes to an entity.
 *
 * Instances of this observer class subscribe to each entity and pass messages on to the frontend.
 */
class Observer : public IObserver {
 public:
  Observer(IController& controller) : controller_(controller) {}

  /**
  * @brief Destructor for Observer.
  */
  virtual ~Observer() {}

  /**
  * @brief Takes messages from entities and passes them onto the frontend.
  * @param message string message to be displayed by frontend
  */
  void Update(const std::string& message) override;

 private:
  IController& controller_;
};

#endif
