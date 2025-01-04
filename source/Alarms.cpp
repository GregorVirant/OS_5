#include "include/Alarms.h"
#include <unistd.h>
#include <sys/file.h>
#include <fstream>
#include <iostream>

Alarms::Alarms(){}
Alarms::Alarms(std::string path){
    int fd = open(path.c_str(),O_RDONLY);
    if (fd == -1){
        std::cerr<<"Error openning file for reading\n";
        return;
    }
    if (flock(fd,LOCK_SH) == -1){
        std::cerr<<"Error locking file.\n";
        close(fd);
        return;
    }
    std::ifstream file(path);

    int lines = 0;
    std::string arg;
    std::string line;

    while(std::getline(file,line)){
        arg += line+"\n";
        lines++;
        if(lines>=4){
            try{
                try {
                    Alarm e1 (arg);
                    alarmList.push_back(e1);
                }
                catch (std::exception& e){
                    std::cerr<<"Creating alarms from file failed: "<<e.what()<<"\n";
                    flock(fd,LOCK_UN);
                    close(fd);
                    return;
                }
            }
            catch (std::exception& e){
                std::cerr<<"Creating even from \"" << arg  <<"\" failed: "<< e.what();
                flock(fd,LOCK_UN);
                close(fd);
                return;
            }
            lines = 0;
            arg = "";
        }
    }
    flock(fd,LOCK_UN);
    close(fd);
}
void Alarms::addAlarm(Alarm alarm){
    alarmList.push_back(alarm);
}
void Alarms::addAlarm(std::string alarmString){
        try{
        Alarm ev(alarmString);
        alarmList.push_back(ev);
    }
    catch(std::exception& e){
        std::cerr<<"Adding alarm through string failed "<<e.what();
    }
}
std::string Alarms::toString() const{
    std::string out;
    for (auto event : alarmList){
        out += event.toString() + "\n\n";
    }
    return out;
}
std::string Alarms::toStringForWriting() const{
    std::string out;
    for (auto event : alarmList){
        out += event.toStringForWriting() + "\n";
    }
    return out;
}
bool Alarms::writeToFile(std::string path) const{
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        std::cerr<<"Error opening the file. \n";
        return false;
    }
    if (flock(fd, LOCK_EX) == -1){
        std::cerr << "Error locking the file.";
        close(fd);
        return false;
    }
    auto str = toStringForWriting();
    auto res = write(fd,str.c_str(),str.size());
    if (res == -1){
        std::cerr<<"Error writing to file.";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }
    flock(fd,LOCK_UN);
    close(fd);
    return true;
}