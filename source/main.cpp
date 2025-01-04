#include "include/Alarms.h"
using namespace std;

int main() { //!!!!!!!!!!!!CATCH ALL THROWN ERRORS
    // vector<bool> v1(7,0);
    // v1[3]=true;
    // Alarm a("Alarm 1",Time(19,30),v1,false,true);
    // cout<<a.toString()<<"\n";
    // Events events;
    // events.addEvent(Event("Event 1",DateTime(4,1,2025,12,12,52),vector<size_t>()));
    // events.addEvent(Event("Event 2",DateTime(4,1,2025,12,12,52),vector<size_t>(3,2)));
    // events.addEvent(Event("Event 3",DateTime(4,1,2025,12,12,52),vector<size_t>()));
    

    // cout << events.toString();
    // events.writeToFile("DB");
    // Events e2 ("DB");
    // cout<<e2.toStringForWriting();
    Alarms a;
    vector<bool> v1(7,0); 
    Alarm a1("Alarm 1",Time(19,30),v1,false,true);
    v1[3]=true;
    Alarm a2("Alarm 2",Time("00 24"),v1,1,0);
    a.addAlarm(a1);
    a.addAlarm(a2);
    //cout<<a.toString();
    a.writeToFile("DB"); 
    Alarms b("DB");
    cout<<b.toString();
}