#include "include/Alarms.h"
#include "include/UI.h"
using namespace std;

int main() {
    // Alarms a;
    // vector<bool> v1(7,0); 
    // Alarm a1("Alarm 1",Time(19,30),v1,false,true);
    // Alarm a2("Alarm 2",Time(19,30),v1,false,true);
    // Alarm a3("Alarm 3",Time(19,30),v1,false,true);
    // Alarm a4("Alarm 4",Time(19,30),v1,false,true);
    // v1[3]=true;
    // Alarm a5("Alarm 5",Time("00 24"),v1,1,0);
    // Alarm a6("Alarm 6",Time("00 24"),v1,1,0);
    // a.addAlarm(a1,"DB"); a.addAlarm(a2,"DB");
    // a.addAlarm(a3,"DB"); a.addAlarm(a4,"DB");
    // a.addAlarm(a5,"DB"); a.addAlarm(a6,"DB");
    // vector<bool> v1(7,0); 
    // Alarm b1("REPLACER",Time("00 24"),v1,1,0);
    // Alarms b("DB");
    // //b.updateAlarm(5,"DB",b1);
    // b.deleteAlarm(3,"DB");

    Alarms a("DB");
    UI ui;
    bool run = true;
    while(run){
        ui.handleInput(run,a,"DB");
    }
    // //cout<<a.toString();
    // a.writeToFile("DB"); 
    // Alarms b("DB");
    // cout<<b.toString();


}