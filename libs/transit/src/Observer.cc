#include "IEntityObserver.h"

class Observer : public IObserver {
  public:
    Observer(Subject &subject) : subject_(subject) {
        this->subject_.Attach(this);
        this->number_ = Observer::static_number_;
    }

    virtual ~Observer() {}

    void Update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;

        // send_update_to_view(string message)?
    }


  private:
    std::string message_from_subject_;
    IEntity &entity_;
    static int static_number_;
    int number_;
    IController& controller;
};