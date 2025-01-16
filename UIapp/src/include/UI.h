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


    bool writingTitle = false;
    std::string writingStringTitle = "";
    bool writingTime = false;
    std::string writingStringTime = "";

    size_t choice_menu_change = 0;
    size_t indexOfAlarm = 0; //alarm being updated
    Alarm alarmUnderUpdate;

    void updateMenu();
public:
    UI();
    ~UI();
    void redoMenuNew();
    void handleInput(bool &running,Alarms &a,const std::string &path);
};


#endif