#include "include/Alarms.h"
#include "include/UI.h"
using namespace std;

int main() {
    Alarms a("DB");
    UI ui;
    bool run = true;
    while(run){
        ui.handleInput(run,a,"DB");
    }
}