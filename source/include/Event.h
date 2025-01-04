#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <sstream>
#include "DateTime.h"

class Event{
private:
    std::string title;
    DateTime dateTime;
public:
    Event(std::string title,DateTime dateTime)
        :title(title),dateTime(dateTime){}
    Event(std::string event):dateTime(0,0,0,0,0,0){
        std::istringstream ss(event);
        std::string dtString;

        if (!std::getline(ss,title)){
            throw std::invalid_argument("Event is missing a title.");
        }
        if (!std::getline(ss,dtString)){
            throw std::invalid_argument("Event is missing date time.");
        }
        dateTime = DateTime(dtString);
    }
    std::string toString() const{
        return title + "\n" + dateTime.toString();
    };
    std::string toStringForWriting() const{
        return title + "\n" + dateTime.toEpochString();
    };

};

#endif