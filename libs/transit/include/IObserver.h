#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <iostream>
#include <list>
#include <string>

/**
 * @class IObserver
 * @brief Represents an observer that subscribes to an entity.
 *
 * Each time an entity is built by a factory, an observer instance subscribes to the entity. 
 * The entity notifies it's observer(s) by calling the Update function. 
 * The observer communicates the message to the front end by calling the controller's SendEventToView function.
 */
class IObserver {
 public:
    /**
     * @brief Virtual destructor for IObserver.
     */
    virtual ~IObserver() {}

    /**
     * @brief Takes message from Entities and communicates with front end to print message to screen
     * @param message string message to be printed to screen
     */
    virtual void Update(const std::string& message) = 0;
};

#endif
