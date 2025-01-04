#ifndef EVENTS_H
#define EVENTS_H

#include <vector>
#include <iostream>
#include "Event.h"

class Events {
private:
    std::vector<Event> eventList;
public:
    Events();
    Events(std::string path);
    void addEvent(Event e);
    void addEvent(std::string str);
    std::string toString() const;
    std::string toStringForWriting() const;
    bool writeToFile(std::string path) const;
    
};

#endif