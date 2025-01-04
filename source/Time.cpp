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
}
bool Time::isLaterOrEqualThan(Time t1){
    if (hours < t1.hours) return false;
    if (hours == t1.hours && minutes < t1.minutes) return false;
    return true;
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