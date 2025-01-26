#include "include/Alarms.h"
#include "include/UI.h"
using namespace std;

int main() {
    std::string db_path = "../DB";
    Alarms a(db_path);
    UI ui;
    bool run = true;
    while(run){
        ui.handleInput(run,a,db_path);
    }
}