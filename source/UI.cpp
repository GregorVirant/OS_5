#include "include/UI.h"
#include <iostream>
#include <sstream>

UI::UI(){
    initscr();
    cbreak();
    noecho();

    std::stringstream ss;
    ss<<"Gregas volume maneger:\n\n";
    ss<<"Chose intput/output:\n";
    ss<<"  1 => input\n";
    ss<<"  2 => output\n";
    ss<<"  3 => mixer\n";
    ss<<"  4 => go back\n";
    ss<<"  q => exit   \n";
    menus.push_back(ss.str());
    ss.str("");
    ss.clear();
    std::cout<<ss.str()<<"\n";
    ss<<"Gregas volume maneger:\n\n";
    ss<<"Input volume:\n";
    ss<<"  1 => increase by 10%\n";
    ss<<"  2 => decrese by 10%\n";
    ss<<"  3 => set to ...\n";    
    ss<<"  4 => input devices\n";
    ss<<"  5 => go back\n";
    ss<<"  q => exit   \n";
    menus.push_back(ss.str());
    ss.str("");
    ss.clear();
    ss<<"Gregas volume maneger:\n\n";
    ss<<"Output volume:\n";
    ss<<"  1 => increase by 10%\n";
    ss<<"  2 => decrese by 10%\n";
    ss<<"  3 => set to ...\n";    
    ss<<"  4 => output devices\n";
    ss<<"  5 => go back\n";
    ss<<"  q => exit   \n";
    menus.push_back(ss.str());
    ss.str("");
    ss.clear();
    updateMenu();
}
UI::~UI() {
    endwin();
}
void UI::updateMenu(){
    if (menus.size()<=currentMenu){
        std::cerr<<"ERROR: this menu doesnt exist.";
        return;
    }
    clear();
    mvprintw(1,0,"%s", menus[currentMenu].c_str());
    refresh();
}
void UI::handleInput(bool &running){
    char ch = getch();
    if (ch == 'q' || (currentMenu == 0 && ch == '4')){
        running = false;
        return;
    }
    if (currentMenu == 0){
        if (ch == '1'){
            currentMenu = 1;
        }
        if (ch == '2'){
            currentMenu = 2;
        }
    }
    if (currentMenu == 1){
        if (ch == '5'){
            currentMenu = 0;
        }
    }
    if (currentMenu == 2){
        if (ch == '5'){
            currentMenu = 0;
        }
    }
    updateMenu();
}

void UI::write(const std::string& message, int x, int y) {
    mvprintw(y, x, "%s", message.c_str());
    refresh();
}

char UI::getInput() {
    return getch();
}
