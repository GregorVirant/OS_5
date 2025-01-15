#include "include/UI.h"
#include <iostream>
#include <sstream>

UI::UI():alarm("Alarm NEW",Time("12 00"),std::vector<bool>(7,0),false,false){
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
    ss<<"Gregas alarm sercvice:\n";
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
    if (currentMenu == 1){
        scrollok(stdscr, FALSE);
        
        /*    
        std::string title;
        Time time;
        std::vector <bool> days;
        bool repeat;
        bool enabled;
        */

        if (choice_menu_new == 0){
            attron(A_REVERSE);
            mvprintw(4,0,"%s","Title: \n\n");
            attroff(A_REVERSE);
        }
        else mvprintw(4,0,"%s","Title: \n\n");

        if (choice_menu_new == 1){
            attron(A_REVERSE);
            printw("%s","Time: \n\n");
            attroff(A_REVERSE);
        }
        else printw("%s","Time: \n\n");

        if (choice_menu_new == 2){
            attron(A_REVERSE);
            printw("%s","SUN  ");
            attroff(A_REVERSE);
        }
        else printw("%s","SUN  ");
        if (choice_menu_new == 3){
            attron(A_REVERSE);
            printw("%s","MON  ");
            attroff(A_REVERSE);
        }
        else printw("%s","MON  ");
        if (choice_menu_new == 4){
            attron(A_REVERSE);
            printw("%s","TUE  ");
            attroff(A_REVERSE);
        }
        else printw("%s","TUE  ");
        if (choice_menu_new == 5){
            attron(A_REVERSE);
            printw("%s","WED  ");
            attroff(A_REVERSE);
        }
        else printw("%s","WED  ");
        if (choice_menu_new == 6){
            attron(A_REVERSE);
            printw("%s","THU  ");
            attroff(A_REVERSE);
        }
        else printw("%s","THU  ");
        if (choice_menu_new == 7){
            attron(A_REVERSE);
            printw("%s","FRI  ");
            attroff(A_REVERSE);
        }
        else printw("%s","FRI  ");
        if (choice_menu_new == 8){
            attron(A_REVERSE);
            printw("%s","SAT\n\n");
            attroff(A_REVERSE);
        }
        else printw("%s","SAT\n\n");
        if (choice_menu_new == 9){
            attron(A_REVERSE);
            printw("%s","REAPEAT   ");
            attroff(A_REVERSE);
        }
        else printw("%s","REAPEAT   ");
        if (choice_menu_new == 10){
            attron(A_REVERSE);
            printw("%s","ENABLED\n\n");
            attroff(A_REVERSE);
        }
        else printw("%s","ENABLED\n\n");
        if (choice_menu_new == 11){
            attron(A_REVERSE);
            printw("%s","SAVE   ");
            attroff(A_REVERSE);
        }
        else printw("%s","SAVE   ");
        if (choice_menu_new == 12){
            attron(A_REVERSE);
            printw("%s","CANCEL");
            attroff(A_REVERSE);
        }
        else printw("%s","CANCEL");
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
    }
    else if (currentMenu == 1){
        if((ch == KEY_DOWN || ch == 'j')&&choice_menu_new<menu_new_size-2){ //-2 ker tist je ze v zadni vrsti
            if (choice_menu_new == 2)choice_menu_new+=7;
            else if (choice_menu_new>2 && choice_menu_new<9)choice_menu_new += 9-choice_menu_new;
            else if (choice_menu_new == 9)choice_menu_new+=2;
            else choice_menu_new++;
        }
        if ((ch == 'l' || ch == KEY_RIGHT)&&((choice_menu_new>=2 && choice_menu_new < 8)||choice_menu_new == 9||choice_menu_new == 11)&&choice_menu_new<menu_new_size-1){
            choice_menu_new++;
        }
        if((ch == KEY_UP || ch == 'k')&&choice_menu_new > 0){
            if (choice_menu_new == 11)choice_menu_new-=2;
            else if (choice_menu_new > 2 && choice_menu_new <= 8)choice_menu_new -= choice_menu_new-1;
            else if (choice_menu_new == 12)choice_menu_new -= 3;
            else if (choice_menu_new == 10)choice_menu_new -= 8;
            else if (choice_menu_new == 9)choice_menu_new-=7;
            else choice_menu_new--;
        }
        if ((ch == KEY_LEFT || ch == 'h')&&((choice_menu_new>2 && choice_menu_new<= 8)||choice_menu_new==12||choice_menu_new == 10)&&choice_menu_new > 0){
            choice_menu_new--;
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
