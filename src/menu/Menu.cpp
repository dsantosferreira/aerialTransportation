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
             "|<<<<<<<<<<<<<<<<<>  Menu  <>>>>>>>>>>>>>>>>>>|\n"
             "|---------------------------------------------|\n";

    for(int i=0; i<this->buttons.size();i++){
        display+="| ["+to_string(i+1)+"] "+this->buttons[i];
        for(int j=0; j<(39-this->buttons[i].length());j++) display+=" "; //adding spaces to format the menu
        if(i<9) display+=' ';
        display+="|\n";
    }
    display+="|_____________________________________________|\n";
    cout<<display<<endl;
}

void Menu::doAction(int option) {
    actions[option]->execute();
}

vector<MenuItem *> Menu::getActions() {
    return actions;
}
