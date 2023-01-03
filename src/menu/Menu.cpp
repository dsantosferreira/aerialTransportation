#include "Menu.h"

Menu::Menu(string path) {
    ifstream file(path);
    for(string button; getline(file,button);){
        this->buttons.push_back(button);
    }
}

void Menu::addMenuItem(MenuItem* menuItem) {
    actions.push_back(menuItem);
}

vector<string> Menu::getButtons() {
    return buttons;
}

void Menu::draw() const {
    system("clear");
    string display;
    display =" _____________________________________________ \n"
             "|\033[40m<<<<<<<<<<<<<<<<<>  Menu  <>>>>>>>>>>>>>>>>>>\033[0m|\n"
             "|\033[40m_____________________________________________\033[0m|\n";

    for(int i=0; i<this->buttons.size();i++){
        display+="|\033[100m                                             \033[0m|\n";
        display+="|\033[100m ["+to_string(i+1)+"] "+this->buttons[i];
        for(int j=0; j<(39-this->buttons[i].length());j++) display+=" "; //adding spaces to format the menu
        if(i<9) display+=' ';
        display+="\033[0m|\n";

    }
    display+="|\033[100m_____________________________________________\033[0m|\n";
    display+="|\033[40m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\033[0m|\n";
    display+="|\033[40m_____________________________________________\033[0m|\n";
    cout<<display<<endl;
}

void Menu::doAction(int option) {
    actions[option]->execute();
}

vector<MenuItem *> Menu::getActions() {
    return actions;
}