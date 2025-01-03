#ifndef UI_H
#define UI_H

#include <ncurses.h>
#include <string>
#include <vector>

class UI {
private:
    std::vector<std::string> menus;
    size_t currentMenu = 0;
    void updateMenu();
    // std::string menu;
    // std::string menuInput;
    // std::string menuOutput;
public:
    UI();
    ~UI();
    void write(const std::string& message, int x, int y);
    char getInput();
    void handleInput(bool &running);
};


#endif