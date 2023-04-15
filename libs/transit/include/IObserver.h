#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <iostream>
#include <list>
#include <string>
#include "IController.h"

class IObserver
{
public:
    virtual ~IObserver(){};
    virtual void Update(const std::string &message_from_subject) = 0;
};

#endif