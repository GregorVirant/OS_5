//#include <ncurses.h>
#include "ui.h"
using namespace std;

int main() {
    UI ui;
    bool running = true;
    while (running){
        ui.handleInput(running);
    }
    return 0;
}