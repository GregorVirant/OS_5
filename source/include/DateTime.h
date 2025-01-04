#ifndef DT_H
#define DT_H
#include <iostream>
#include <ctime>
#include <sstream>

class DateTime{
private:
    int day;
    int month;
    int year;
    int seconds;
    int minutes;
    int hours;
public:
    DateTime(int day,int month,int year,int hours,int minutes,int seconds)
        :day(day),month(month),year(year),seconds(seconds),minutes(minutes),hours(hours){}
    DateTime(std::string timeEpoch){
        try {
            std::time_t t = std::stoll(timeEpoch);
            std::tm* tm = localtime(&t);
            if(tm == nullptr){
                throw std::invalid_argument("localtime() failed");
            }
            day = tm->tm_mday;
            month = tm->tm_mon + 1;
            year = tm->tm_year + 1900;
            seconds = tm->tm_sec;
            minutes = tm->tm_min;
            hours = tm->tm_hour;
        }
        catch (std::exception& e){
            throw std::invalid_argument("Invalid time epoch string: ");
        }
    }
    std::string toString() const {
        std::stringstream ss;
        ss << day<<"-"<<month<<"-"<<year <<" "<< hours << ":"<<minutes<<":"<< seconds;
        return ss.str();
    }
    std::string toEpochString() const {
        std::tm tm {};
        tm.tm_mday = day;
        tm.tm_mon = month - 1;
        tm.tm_year = year - 1900;
        tm.tm_sec = seconds;
        tm.tm_min = minutes;
        tm.tm_hour = hours;
        return std::to_string(std::mktime(&tm));
    }
    std::size_t toEpoch() const {
        std::tm tm {};
        tm.tm_mday = day;
        tm.tm_mon = month - 1;
        tm.tm_year = year - 1900;
        tm.tm_sec = seconds;
        tm.tm_min = minutes;
        tm.tm_hour = hours;
        return std::mktime(&tm);
    }
    bool operator==(const DateTime& dt1) const {
        return toEpoch() == dt1.toEpoch();
    }
};

#endif