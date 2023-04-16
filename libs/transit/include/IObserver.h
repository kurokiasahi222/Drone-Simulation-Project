#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <iostream>
#include <list>
#include <string>

class IObserver
{
public:
    virtual ~IObserver(){};
    virtual void Update(const std::string& message) = 0;
};

#endif