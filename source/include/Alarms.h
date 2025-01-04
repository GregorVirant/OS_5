#ifndef ALARMS_H
#define ALARMS_H

#include <vector>
#include <iostream>
#include "Alarm.h"

class Alarms{
private:
    std::vector<Alarm> alarmList;
public:
    Alarms();
    Alarms(std::string path);
    void addAlarm(Alarm alarm);
    void addAlarm(std::string alarmString);
    std::string toString() const;
    std::string toStringForWriting() const;
    bool writeToFile(std::string path) const;
};

#endif