#include "IEntityOberver.h"

class Observer : public IObserver {
  public:
    Observer(Subject &subject) : subject_(subject) {
        this->subject_.Attach(this);
        // std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }

    virtual ~Observer() {}

    void Update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        // create json object
        // PrintInfo(); 
        // send_update_to_view()?
    }

    // void RemoveMeFromTheList_because_bought() {
    //     subject_.Detach(this);
    //     std::cout << "Observer \"" << number_ << "\" bought a PS5.\n";
    // }

    // void RemoveMeFromTheList_because_impatient() {
    //     subject_.Detach(this);
    //     std::cout << "Observer \"" << number_ << "\" got impatient and left.\n";
    // }

    // void PrintInfo() {
    //     std::cout << "Observer \"" << this->number_ << "\": a new message is available
    //     --> " << this->message_from_subject_ << "\n";
    // }

  private:
    std::string message_from_subject_;
    IEntity &entity_;
    static int static_number_;
    int number_;
    IController& controller;
};