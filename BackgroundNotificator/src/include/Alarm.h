#ifndef ALARM_H
#define ALARM_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Time.h"

class Alarm{
public:
    std::string title;
    Time time;
    std::vector <bool> days;
    bool repeat;
    bool enabled;

    Alarm(std::string title,Time time,std::vector <bool> days,bool repeat,bool enabled);
    Alarm(std::string alarm);
    std::string toString() const;
    std::string toStringForWriting() const;
};

#endif