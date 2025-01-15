#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <string>
#include <vector>
#include "Alarms.h"

class UI {
private:
    std::vector<std::string> menus;
    size_t currentMenu = 0;
    size_t choice_menu_new = 0;
    size_t menu_new_size = 13;
    size_t choice_menu_1 = 0;

    void updateMenu();
    // std::string menu;
    // std::string menuInput;
    // std::string menuOutput;
public:
    UI();
    ~UI();
    void handleInput(bool &running,Alarms a);
};


#endif