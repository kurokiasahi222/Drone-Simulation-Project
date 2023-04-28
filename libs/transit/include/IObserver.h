#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <iostream>
#include <list>
#include <string>

/**
 * @class IObserver
 * @brief Abstract observer that subscribes to an entity.
 *
 * This is the interface used by the entity to notify its observers, so that the
 * entity doesn't have to directly reference a concrete observer class.
 */
class IObserver {
 public:
    /**
     * @brief Destructor for IObserver.
     */
    virtual ~IObserver() {}

    /**
     * @brief Abstract function for accepting input from an entity
     * @param message string message from entity
     */
    virtual void Update(const std::string& message) = 0;
};

#endif
