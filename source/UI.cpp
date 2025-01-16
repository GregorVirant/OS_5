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
void UI::redoMenuNew(){
    choice_menu_new = 0;
    Alarm a("Alarm NEW",Time("12 00"),std::vector<bool>(7,0),false,false);
    alarm = a;
}
void UI::handleInput(bool &running,Alarms &a,const std::string &path){
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
            if (!writingTitle) 
                printw("%s",(alarm.title).c_str());
            else 
                printw("%s",writingStringTitle.c_str());
        }
        printw("%s","\n\n");
        if (choice_menu_new == 1){
            attron(A_REVERSE);
            printw("%s","Time:  ");
            printw("%s",(alarm.time.toStringForWriting()+"\n\n").c_str());
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
