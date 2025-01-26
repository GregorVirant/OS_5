#ifndef T_H
#define T_H

#include <iostream>
#include <ctime>
#include <sstream>

class Time{
public:
    int hours;
    int minutes;
    int seconds;
    Time():hours(0),minutes(0),seconds(0){}
    Time(int hours,int minutes);
    Time(std::string str);
    bool isEqual(Time t1);
    std::string toString() const;
    std::string toStringForWriting() const;
};

#endif