#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "IObserver.h"
#include "IController.h"

class Observer : public IObserver {
 public:
  Observer(IController& controller) : controller_(controller) {}

  virtual ~Observer() {}

  void Update(const std::string& message) override;

 private:
  IController& controller_;
};

#endif
