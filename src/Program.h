#ifndef AERIALTRANSPORTATION_PROGRAM_H
#define AERIALTRANSPORTATION_PROGRAM_H

#include "menu/Menu.h"
#include "menu/change/ChangeMenu.h"
#include "menu/search/Search.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Program {
private:
    int currMenuPage;
    vector<Menu> menus;
    Database database;

    void createMainMenu();
    void createMenu1();
    void createMenu2();

public:
    Program();
    void run();
    int getMenuOption(int &option, int nButtons);
    void cleanMenus();
};


#endif
