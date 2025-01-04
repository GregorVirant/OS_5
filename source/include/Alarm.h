#ifndef ALARM_H
#define ALARM_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Time.h"

class Alarm{
private:
    std::string title;
    Time time;
    std::vector <bool> days;
    bool repeat;
    bool enabled;
public:
    Alarm(std::string title,Time time,std::vector <bool> days,bool repeat,bool enabled);
    Alarm(std::string alarm);
    std::string toString() const;
    std::string toStringForWriting() const;
    bool isItToday(int today); ////////////////////////////////////
    bool shouldTrigger(); //check time and if its today and if enabled ////////////////////////////////////
    void callOnTrigger(); //removes current day if not set to reapeating ////////////////////////////////////

    //MAYBE FIRSTTRIGGER
};

#endif