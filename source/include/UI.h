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
    Alarm alarm;
    //#Alarm newAlarm("Alarm NEW",Time("12 00"),std::vector<bool>(7,0),false,false);

    void updateMenu();
    // std::string menu;
    // std::string menuInput;S
    // std::string menuOutput;
public:
    UI();
    ~UI();
    void redoMenuNew();
    void handleInput(bool &running,Alarms &a,const std::string &path);
};


#endif