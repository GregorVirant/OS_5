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
                    Alarm e1(arg);
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
bool Alarms::addAlarm(Alarm alarm,std::string path){
    alarmList.push_back(alarm);
    int fd = open(path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1){
        std::cerr<<"Error opening the file. \n";
        return false;
    }
    if (flock(fd, LOCK_EX) == -1){
        std::cerr << "Error locking the file.";
        close(fd);
        return false;
    }
    auto str = alarm.toStringForWriting()+"\n";
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
bool Alarms::deleteAlarm(size_t index,std::string path){
    if (index >= alarmList.size()){
        std::cerr<<"Error: invalid index.";
        return false;
    }
    alarmList.erase(alarmList.begin()+index);

    int fd = open(path.c_str(),O_RDWR, 0644);
    if (fd == -1){
        std::cerr<<"Error: openning file (delete)";
        return false;
    }
    if (flock(fd,LOCK_EX) == -1){
        std::cerr<<"Error: locking file (delete)";
        close(fd);
        return false;
    }
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr<<"Error: openning file (delete)1";
        flock(fd,LOCK_UN);
        close(fd);
        return false;
    }
    std::string newContent;
    std::string line;
    size_t count = 0;
    while(std::getline(file,line)){
        count++;
        if(!(4*index<count && 4*index + 4 >= count))
            newContent+=line + "\n";
    }
    file.close();
    if (lseek(fd, 0, SEEK_SET) == -1) {
        std::cerr << "Error seeking to start. (Delete)";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }

    if (ftruncate(fd, 0) == -1) {
        std::cerr << "Error clearing file. (Delete)";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }
    if (write(fd,newContent.c_str(),newContent.size()) == -1){
        std::cerr<<"Error writing new content to file. (Delete)";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }
    flock(fd, LOCK_UN);
    close(fd);
    return true;
}
bool Alarms::updateAlarm(size_t index, std::string path, Alarm newAlarm){
    if (index >= alarmList.size()){
        std::cerr<<"Error: invalid index.";
        return false;
    }
    alarmList[index]=newAlarm;

    int fd = open(path.c_str(),O_RDWR, 0644);
    if (fd == -1){
        std::cerr<<"Error: openning file (delete)";
        return false;
    }
    if (flock(fd,LOCK_EX) == -1){
        std::cerr<<"Error: locking file (delete)";
        close(fd);
        return false;
    }
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr<<"Error: openning file (delete)1";
        flock(fd,LOCK_UN);
        close(fd);
        return false;
    }
    std::string newContent;
    std::string line;
    size_t count = 0;
    while(std::getline(file,line)){
        count++;
        if(!(4*index<count && 4*index + 4 >= count))
            newContent+=line + "\n";
        if(count == 4 * index + 4){
            newContent += newAlarm.toStringForWriting() + "\n";
        }
    }
    file.close();
    if (lseek(fd, 0, SEEK_SET) == -1) {
        std::cerr << "Error seeking to start. (Delete)";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }

    if (ftruncate(fd, 0) == -1) {
        std::cerr << "Error clearing file. (Delete)";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }
    if (write(fd,newContent.c_str(),newContent.size()) == -1){
        std::cerr<<"Error writing new content to file. (Delete)";
        flock(fd, LOCK_UN);
        close(fd);
        return false;
    }
    flock(fd, LOCK_UN);
    close(fd);
    return true;
}