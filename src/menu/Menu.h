#ifndef AERIALTRANSPORTATION_MENU_H
#define AERIALTRANSPORTATION_MENU_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "MenuItem.h"

using namespace std;

class Menu
{
private:
    vector<string> buttons;
    vector<MenuItem *> actions;

public:
    Menu(string path);
    vector<string> getButtons();
    void draw() const;
    void addMenuItem(MenuItem *menuItem);
    void doAction(int option);
    vector<MenuItem *> getActions();
};

#endif
