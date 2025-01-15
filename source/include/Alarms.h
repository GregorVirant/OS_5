#ifndef ALARMS_H
#define ALARMS_H

#include <vector>
#include <iostream>
#include "Alarm.h"

class Alarms{
private: 
public:
    std::vector<Alarm> alarmList;
    Alarms();
    Alarms(std::string path);
    bool addAlarm(Alarm alarm,std::string path); 
    //write last alarm    that writes newest addet alarm to file
    //deleteAlarm(size_t index)  delete specific alarm
    bool deleteAlarm(size_t index,std::string path);
    bool updateAlarm(size_t index, std::string path, Alarm newAlarm);
    //updateAlarm(size_t index, std::string path,Alarm newAlarm) replaces alarm in our vector and also updates 4 lines that belong to it in file
    void addAlarm(std::string alarmString);
    std::string toString() const;

    //write new


    // std::string toStringForWriting() const;
    // bool writeToFile(std::string path) const;
    //Write new alarm at the end of the file
    //Override one alarm (string path, size_t alarmIndex,Alarm a)  read from file and then write only one alarm
    //
};

#endif