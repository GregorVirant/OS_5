#include "include/UI.h"
#include <iostream>
#include <sstream>

UI::UI():alarm("Alarm NEW",Time("12 00"),std::vector<bool>(7,0),false,false),alarmUnderUpdate("Alarm NEW",Time("12 00"),std::vector<bool>(7,0),false,false){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    refresh();

    std::stringstream ss;
    ss<<"Gregas alarm sercvice:\n";
    ss<<"q-quit  h-help\n\n";
    menus.push_back(ss.str());
    ss.str("");
    ss.clear();

    std::cout<<ss.str()<<"\n";
    ss<<"Gregas alarm sercvice:\n";
    ss<<"Creating new alarm.\n\n";
    menus.push_back(ss.str());
    ss.str("");
    ss.clear();

    ss<<"Gregas alarm sercvice:\n";
    menus.push_back(ss.str());
    ss.str("");
    ss.clear();

    ss<<"Gregas alarm sercvice:\n\n";
    ss<<"HELP:\n";
    ss<<"q-quit\n";
    ss<<"When lunching the app a menu will show up, you can navigate the menu using arrows on keyboard or vim keybinds (hjkl). To confirm the choice you click ENTER. ";
    ss<<"There are two things you can do, you can select \"NEW ALARM\" button to bring up a menu for creating a new alarm. The other option is to select an existing ";
    ss<<"alarm. After doing that a menu with 2 options will be displayed. One is to delete the alarm the other one is for activation/deactiovation.\n\nFor choosing a name ";
    ss<<"you will enter input mode in which you can only add/remove letters to exit it you can either click enter for confirming new name and escape to exit this menu reeverting to the previous state.\n";

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
void UI::redoMenuNew(){
    choice_menu_new = 0;
    Alarm a("Alarm NEW",Time("12 00"),std::vector<bool>(7,0),false,false);
    alarm = a;
}
void UI::handleInput(bool &running,Alarms &a,const std::string &path){
    scrollok(stdscr, TRUE);
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
    }
    else if (currentMenu == 1){
        scrollok(stdscr, FALSE);
        if (choice_menu_new == 0){
            attron(A_REVERSE);
            
            if (!writingTitle){
                mvprintw(4,0,"%s","Title: ");
                printw("%s",(alarm.title).c_str());
            }
            else {
                attroff(A_REVERSE);
                attron(A_BOLD);
                mvprintw(4,0,"%s","Title: ");
                printw("%s",writingStringTitle.c_str());
                attroff(A_BOLD);
            }
            attroff(A_REVERSE);
        }
        else {
            mvprintw(4,0,"%s","Title: ");
            printw("%s",(alarm.title).c_str());
        }
        printw("%s","\n\n");
        if (choice_menu_new == 1){
            attron(A_REVERSE);
            if (!writingTime){
                printw("%s","Time:  ");
                printw("%s",(alarm.time.toStringForWriting()+"\n\n").c_str());
            }
            else {
                attroff(A_REVERSE);
                attron(A_BOLD);
                printw("%s","Time:  ");
                printw("%s",(writingStringTime+"\n\n").c_str());
                attroff(A_BOLD);
            }
            attroff(A_REVERSE);
        }
        else {
            printw("%s","Time:  ");
            printw("%s",(alarm.time.toStringForWriting()+"\n\n").c_str());
        }

        if (choice_menu_new == 2){
            if (alarm.days[0])attron(A_UNDERLINE); 
            attron(A_REVERSE);
            printw("%s","SUN");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.days[0])attron(A_UNDERLINE); 
            printw("%s","SUN");
        }
        attroff(A_UNDERLINE); 
        printw("%s","  ");

        if (choice_menu_new == 3){
            if (alarm.days[1])attron(A_UNDERLINE); 
            attron(A_REVERSE);
            printw("%s","MON");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.days[1])attron(A_UNDERLINE); 
            printw("%s","MON");
        }
        attroff(A_UNDERLINE); 
        printw("%s","  ");

        if (choice_menu_new == 4){
            if (alarm.days[2])attron(A_UNDERLINE); 
            attron(A_REVERSE);
            printw("%s","TUE");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.days[2])attron(A_UNDERLINE); 
            printw("%s","TUE");
        }
        attroff(A_UNDERLINE);
        printw("%s","  ");

        if (choice_menu_new == 5){
            if (alarm.days[3])attron(A_UNDERLINE); 
            attron(A_REVERSE);
            printw("%s","WED");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.days[3])attron(A_UNDERLINE); 
            printw("%s","WED");
        }
        attroff(A_UNDERLINE); 
        printw("%s","  ");

        if (choice_menu_new == 6){
            if (alarm.days[4])attron(A_UNDERLINE); 
            attron(A_REVERSE);
            printw("%s","THU");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.days[4])attron(A_UNDERLINE); 
            printw("%s","THU");
        }
        attroff(A_UNDERLINE); 
        printw("%s","  ");

        if (choice_menu_new == 7){
            if (alarm.days[5])attron(A_UNDERLINE); 
            attron(A_REVERSE);
            printw("%s","FRI");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.days[5])attron(A_UNDERLINE); 
            printw("%s","FRI");
        }
        attroff(A_UNDERLINE); 
        printw("%s","  ");

        if (choice_menu_new == 8){
            if (alarm.days[6])attron(A_UNDERLINE); 
            attron(A_REVERSE);
            printw("%s","SAT\n\n");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.days[6])attron(A_UNDERLINE); 
            printw("%s","SAT\n\n");
        }
        attroff(A_UNDERLINE); 
        if (choice_menu_new == 9){
            attron(A_REVERSE);
            if (alarm.repeat) attron(A_UNDERLINE);
            printw("%s","REAPEAT");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.repeat) attron(A_UNDERLINE);
            printw("%s","REAPEAT");
        }
        attroff(A_UNDERLINE);
        printw("%s","   ");
        if (choice_menu_new == 10){
            if (alarm.enabled) attron(A_UNDERLINE);
            attron(A_REVERSE);
            printw("%s","ENABLED\n\n");
            attroff(A_REVERSE);
        }
        else {
            if (alarm.enabled) attron(A_UNDERLINE);
            printw("%s","ENABLED\n\n");
        }
        attroff(A_UNDERLINE);
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
    else if (currentMenu == 2){
        alarmUnderUpdate = a.alarmList[indexOfAlarm];
        printw("%s",(alarmUnderUpdate.toString()+"\n").c_str());

        if (choice_menu_change == 0) attron(A_REVERSE);
        printw("%s","BACK");
        attroff(A_REVERSE);
        printw("%s","  ");
        if (choice_menu_change == 1) attron(A_REVERSE);
        printw("%s","DELETE");
        attroff(A_REVERSE);
        printw("%s","  ");
        if (choice_menu_change == 2) attron(A_REVERSE);
        printw("%s","ENABLE/DISABLE");
        attroff(A_REVERSE);
    }
    else if (currentMenu == 3){
        attron(A_REVERSE);
        printw("%s","BACK");
        attroff(A_REVERSE);
    }
    
    int ch = getch();
    if (ch == 'q' && !(writingTime || writingTitle)){
        running = false;
        return;
    }
    if (ch == 'h' && currentMenu == 0){
        currentMenu = 3;
        updateMenu();
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
            else{
                indexOfAlarm = choice_menu_1 - 1;
                currentMenu = 2;
                updateMenu();
            }
        }
    }
    else if (currentMenu == 1){
        if (writingTitle){
            if(ch == KEY_ENTER || ch == 10){
                writingTitle = false;
                alarm.title = writingStringTitle;
                writingStringTitle = "";
            }
            else if(ch == 27){
                writingTitle = false;
                writingStringTitle = "";
            }
            else if(isprint(ch)){
                writingStringTitle += ch;
            }
            else if (ch == KEY_BACKSPACE || ch == 127){
                if(!writingStringTitle.empty()){
                    writingStringTitle.pop_back();
                }
            }
            updateMenu();
            return;
        }
        if (writingTime){
            if(ch == KEY_ENTER || ch == 10){
                writingTime = false;
                try{
                    alarm.time = Time(writingStringTime); ///////////CATCH ERROR
                }
                catch (std::exception &e){
                    mvprintw(0,0,"%s","\nTime input should be  in format hh mm");
                }
                writingStringTime = "";
            }
            else if(ch == 27){
                writingTime = false;
                writingStringTime = "";
            }
            else if(isprint(ch)){
                writingStringTime += ch;
            }
            else if (ch == KEY_BACKSPACE || ch == 127){
                if(!writingStringTime.empty()){
                    writingStringTime.pop_back();
                }
            }
            updateMenu();
            return;
        }
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
        if(ch == KEY_ENTER || ch == 10){
            if (choice_menu_new == 0){
                writingTitle = true;
            }
            if (choice_menu_new == 1){
                writingTime = true;
            }
            if (choice_menu_new >= 2 && choice_menu_new <= 8){
                alarm.days[choice_menu_new-2] = not alarm.days[choice_menu_new-2];
            }
            if (choice_menu_new == 9){
                alarm.repeat = not alarm.repeat;
            }
            if (choice_menu_new == 10){
                alarm.enabled = not alarm.enabled;                
            }
            if (choice_menu_new == 11){ //SAVE
                currentMenu = 0;
                a.addAlarm(alarm,path);
                redoMenuNew();
            }
            if (choice_menu_new == 12){ //CANCEL
                currentMenu = 0;
                redoMenuNew();
            }
        } 
    }
    else if (currentMenu == 2){
        if((ch == KEY_RIGHT || ch == 'l')&&choice_menu_change<2){
            choice_menu_change++;
        }
        if ((ch == KEY_LEFT || ch == 'h')&&choice_menu_change > 0){
            choice_menu_change--;
        }
        if (ch == KEY_ENTER || ch == 10){
            if (choice_menu_change == 0){
                currentMenu = 0;
            }
            else if (choice_menu_change == 1){
                currentMenu = 0;
                a.deleteAlarm(indexOfAlarm,path);
                choice_menu_1 = 0;
                choice_menu_change = 0;
            }
            else if (choice_menu_change == 2){
                currentMenu = 0;
                alarmUnderUpdate.enabled = not alarmUnderUpdate.enabled;
                a.updateAlarm(indexOfAlarm,path,alarmUnderUpdate);
                choice_menu_1 = 0;
                choice_menu_change = 0;
            }
        }
    }
    else if (currentMenu == 3){
        if(ch == KEY_ENTER || ch == 10){
            currentMenu = 0;
        }
    }

    updateMenu();
}