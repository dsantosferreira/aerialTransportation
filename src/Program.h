#ifndef AERIALTRANSPORTATION_PROGRAM_H
#define AERIALTRANSPORTATION_PROGRAM_H

#include "menu/Menu.h"
#include "menu/change/ChangeMenu.h"
#include "menu/search/Search.h"
#include "menu/show/ShowArtPoints.h"
#include "menu/show/ShowAirports.h"
#include "menu/show/ShowAirlines.h"
#include "menu/search/DirectFlights.h"
#include "menu/search/ReachableDestinations.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Program
{
private:
    /** @var menu page we are currently in */
    int currMenuPage;

    /** @var vector of all the program's menus */
    vector<Menu> menus;

    /** @var program's database where airports, airlines and the flights graph are stored*/
    Database database;

    void createMainMenu();
    void createMenu1();
    void createShowMenu();

public:
    Program();
    void run();
    bool getMenuOption(int &option, int nButtons);
    void cleanMenus();
};

#endif
