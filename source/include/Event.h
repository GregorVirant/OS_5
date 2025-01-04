#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "DateTime.h"

class Event{
private:
    std::string title;
    DateTime dateTime;
    std::vector<DateTime>notify;
public:
    // Event(std::string title,DateTime dateTime)
    //     :title(title),dateTime(dateTime){
    //         notify.push_back(dateTime);
    // }
    Event(std::string title,DateTime dateTime,std::vector<size_t> notifications):title(title),dateTime(dateTime){
        for (auto n : notifications){
            notify.push_back(DateTime(std::to_string(dateTime.toEpoch()-n)));
        }
    }
    Event(std::string event):dateTime(0,0,0,0,0,0){
        std::istringstream ss(event);
        std::string dtString;
        std::string notifies;

        if (!std::getline(ss,title)){
            throw std::invalid_argument("Event is missing a title.");
        }
        if (!std::getline(ss,dtString)){
            throw std::invalid_argument("Event is missing date time.");
        }
        if (!std::getline(ss,notifies)){
            throw std::invalid_argument("Event is missing notifies.");
        }

        std::stringstream ss1(notifies);
        std::string num;
        while(ss1>>num){
            notify.push_back(DateTime(num));
        }

        dateTime = DateTime(dtString);
    }
    std::string toString() const{
        std::string notifies = "";
        for (auto n : notify){
            notifies += n.toString();
            notifies += ", ";
        }
        return title + "\nDateTime: " + dateTime.toString() + "\nNotify at: " + notifies;
    };
    std::string toStringForWriting() const{
        std::string notifies = "";
        for (auto n : notify){
            notifies += n.toEpochString();
            notifies += " ";
        }
        return title + "\n" + dateTime.toEpochString() + "\n" + notifies;
    };
    void removeNotify(DateTime dt){
        notify.erase(std::remove(notify.begin(), notify.end(), dt));
    }
    void addNotify(DateTime dt){
        notify.push_back(dt);
    }
    void changeDateTime(DateTime dt){
        auto diff = dateTime.toEpoch()-dt.toEpoch();
        dateTime = DateTime(dt);
        for (auto n : notify){
            DateTime(std::to_string(n.toEpoch()-diff));
        }
    }
};

#endif