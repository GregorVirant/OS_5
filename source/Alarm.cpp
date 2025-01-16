#include "include/Alarm.h"

Alarm::Alarm(std::string title,Time time,std::vector <bool> days,bool repeat,bool enabled)
    :title(title),time(time),days(days),repeat(repeat),enabled(enabled){
        if (days.size()!=7) throw std::invalid_argument("Days isnt 7 long.");
}
Alarm::Alarm(std::string alarm):days(7,false){
    std::istringstream ss(alarm);
    std::string time1;
    std::string days1;
    std::string args;
    

    if (!std::getline(ss,title)){
        throw std::invalid_argument("Alarm is missing a title.");
    }
    if (!std::getline(ss,time1)){
        throw std::invalid_argument("Event is missing time.");
    }
    if (!std::getline(ss,days1)){
        throw std::invalid_argument("Event is missing days.");
    }
    if (!std::getline(ss,args)){
        throw std::invalid_argument("Event is missing reapeat.");
    }

    time = Time(time1);

    // std::stringstream ss1(days1);
    // size_t num;
    // while(ss1>>num){
    //     if (num >= days.size()) throw std::invalid_argument("Invalid day value.");
    //     days[num] = true;
    // }
    std::stringstream ss1(days1);
    for (size_t i = 0; i<days.size();i++){
        int val;
        if(!(ss1>>val) || (val != 0 && val != 1)){
            throw std::invalid_argument("Days  must contain only 0 or 1 in the DB.");
        }
        days[i] = val;
    }

    std::stringstream ss2(args);
    if (!(ss2>>repeat))throw std::invalid_argument("Event is missing repeat.");
    if (!(ss2>>enabled))throw std::invalid_argument("Event is missing enabled.");
}
std::string Alarm::toString() const{
    std::string dayStr;
    for (auto day : days)
        dayStr+=" " + std::to_string(day)+"  ";
    std::stringstream ss;
    ss<<title<<" "<< time.toString()<<"\n";
    ss<<"SUN MON TUE WED THU FRI SAT\n"<<dayStr<<"\nRepeat:  "<<repeat<<"\nEnabled: "<<enabled;
    return ss.str();
}
std::string Alarm::toStringForWriting() const {
    std::string dayStr;
    for (auto day : days)
        dayStr+=std::to_string(day)+" ";
    std::stringstream ss;
    ss<<title<<"\n"<< time.toStringForWriting()<<"\n"<<dayStr<<"\n"<<repeat<<" "<<enabled;
    return ss.str();
}