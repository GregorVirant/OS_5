#include "include/Alarms.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
void send_notification(std::string title, std::string body){
    std::string notify_str = "notify-send " + title + " " + body;
    system(notify_str.c_str());
}
int main() {
    std::string db_path = "../DB";
    while (true){
        Alarms alarms;
        try{
            alarms = Alarms(db_path);
        }
        catch (std::exception &e){
            std::cerr<<"DB reading error: " << e.what()<<"\n";
            return -1;
        }

        auto now = std::chrono::system_clock::now();
        time_t current_time = std::chrono::system_clock::to_time_t(now);
        tm* local_time = std::localtime(&current_time);

        int current_day = local_time->tm_wday;
        int current_hour = local_time->tm_hour;
        int current_minute = local_time->tm_min;

        for (size_t i = 0; i< alarms.alarmList.size(); i++){
            if (alarms.alarmList[i].days[current_day] && alarms.alarmList[i].time.isEqual(Time(current_hour,current_minute))){
                std::cerr << "Trigering alarm" << std::endl;
                Alarm a1(alarms.alarmList[i]);
                send_notification("ALARM:",a1.title);
                if (!a1.repeat){
                    a1.enabled = false;
                    alarms.updateAlarm(i, db_path, a1);
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(60 - local_time->tm_sec));
    }
}