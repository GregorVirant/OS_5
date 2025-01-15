#include "include/UI.h"
#include <iostream>
#include <sstream>

UI::UI(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    refresh();

    std::stringstream ss;
    ss<<"Gregas alarm sercvice:\n\n";
    // ss<<"Chose intput/output:\n";
    // ss<<"  1 => input\n";
    // ss<<"  2 => output\n";
    // ss<<"  3 => mixer\n";
    // ss<<"  4 => go back\n";
    // ss<<"  q => exit   \n";
    menus.push_back(ss.str());
    ss.str("");
    ss.clear();
    std::cout<<ss.str()<<"\n";
    ss<<"Gregas alarm sercvice:\n\n";
    ss<<"Creating new alarm.\n";
    // ss<<"Input volume:\n";
    // ss<<"  1 => increase by 10%\n";
    // ss<<"  2 => decrese by 10%\n";
    // ss<<"  3 => set to ...\n";    
    // ss<<"  4 => input devices\n";
    // ss<<"  5 => go back\n";
    // ss<<"  q => exit   \n";
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
void UI::handleInput(bool &running,Alarms a){
    scrollok(stdscr, TRUE);
    //scrl(5);
    //scrollok(stdscr, FALSE);
    if (currentMenu == 0){
        if (choice_menu_1 > a.alarmList.size()){
            std::cout<<"NAPAKA: poskusamo posegati zunaj polja alarmLIst";
            running = false;
            return;
        }
        if(choice_menu_1==0){
            attron(A_REVERSE);
            mvprintw(3,0,"%s","NEW ALARM\n\n");
            scrollok(stdscr, FALSE);
            
        }
        else mvprintw(3,0,"%s","NEW ALARM\n\n");
        
        attroff(A_REVERSE);
        for (size_t i = 0; i<a.alarmList.size();i++){
            if (choice_menu_1 == i + 1){
                attron(A_REVERSE);
                printw("%s",(a.alarmList[i].toString()+"\n\n").c_str());
                scrollok(stdscr, FALSE);
                
            }
            else
                printw("%s",(a.alarmList[i].toString()+"\n\n").c_str());
            attroff(A_REVERSE);
        }
        //move(choice_menu_1*5,0);
        //a.alarmList
        //printw("%s",a.toString().c_str());
    }
  
    
    int ch = getch();
    if (ch == 'q' || (currentMenu == 0 && ch == '4')){
        running = false;
        return;
    }
    if (currentMenu == 0){
        if ((ch == KEY_DOWN || ch == 'j')&&choice_menu_1<a.alarmList.size()){
            choice_menu_1++;
        }
        if ((ch == KEY_UP || ch == 'k')&&choice_menu_1 > 0){
            choice_menu_1--;
        }
        if((ch == KEY_ENTER || ch == 10)){
            if (choice_menu_1 == 0){
                currentMenu = 1;
            }
        }
        // if (ch == '2'){
        //     currentMenu = 2;
        // }
        
    }

    else if (currentMenu == 1){
        if (ch == '5'){
            currentMenu = 0;
        }
    }
    else if (currentMenu == 2){
        if (ch == '5'){
            currentMenu = 0;
        }
    }
    updateMenu();
}

// void UI::write(const std::string& message, int x, int y) {
//     mvprintw(y, x, "%s", message.c_str());
//     refresh();
// }

// char UI::getInput() {
//     return getch();
// }
