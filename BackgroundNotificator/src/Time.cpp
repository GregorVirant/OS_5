#include "include/Time.h"

Time::Time(int hours,int minutes)
    :hours(hours),minutes(minutes),seconds(0){}
Time::Time(std::string str){
    std::stringstream ss(str);
    if (!(ss>>hours)){
        throw std::invalid_argument("Napaka pri branju ur.");
    }
    if (!(ss>>minutes)){
        throw std::invalid_argument("Napaka pri branju minut.");
    }
    if (hours < 0 || hours > 23) throw std::invalid_argument("Napaka: nevalidne ure.");
    if (minutes < 0 || minutes > 59) throw std::invalid_argument("Napaka: nevalidne minute.");
}
bool Time::isEqual(Time t1){
    return (hours == t1.hours && minutes == t1.minutes);
}
std::string Time::toString() const {
    std::stringstream ss;
    ss<<hours<<":"<<minutes;
    return ss.str();
}
std::string Time::toStringForWriting() const {
    std::stringstream ss;
    ss<<hours<<" "<<minutes;
    return ss.str();
}