#include "include/Events.h"
using namespace std;

int main() {
    Events events;
    events.addEvent(Event("Event 1",DateTime(4,1,2025,12,12,52),vector<size_t>()));
    events.addEvent(Event("Event 2",DateTime(4,1,2025,12,12,52),vector<size_t>(3,2)));
    events.addEvent(Event("Event 3",DateTime(4,1,2025,12,12,52),vector<size_t>()));
    

    cout << events.toString();
    events.writeToFile("DB");
    Events e2 ("DB");
    cout<<e2.toStringForWriting();

}