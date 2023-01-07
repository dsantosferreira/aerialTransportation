#include <limits>
#include <set>
#include "Program.h"
#include "menu/show/ShowAirport.h"
#include "menu/show/ShowAirline.h"

Program::Program()
{
    currMenuPage = 0;
    database = Database();
    createMainMenu();
    createMenu1();
    createMenu2();
}

void Program::run()
{
    int option;

    while (currMenuPage != -1)
    {
        menus[currMenuPage].draw();

        cout << "Insert an option: ";
        while (getMenuOption(option, menus[currMenuPage].getButtons().size()))
            cout << "\033[31mPlease insert a valid option: \033[0m";

        Menu menu = menus[currMenuPage];
        menu.doAction(option - 1);
    }

    cleanMenus();
}

int Program::getMenuOption(int &option, int nButtons)
{
    cin >> option;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    if (option <= 0 || option > nButtons)
        return true;

    return false;
}

void Program::createMainMenu()
{
    menus.push_back(Menu("../files/mainMenu"));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 1));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 2));
    menus[menus.size() - 1].addMenuItem(new Search(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, -1));
}

void Program::createMenu1()
{
    menus.push_back(Menu("../files/menu1"));
    menus[menus.size() - 1].addMenuItem(new DirectFlights(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ReachableDestinations(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 0));
}

void Program::createMenu2()
{
    menus.push_back(Menu("../files/menu2"));
    menus[menus.size() - 1].addMenuItem(new ShowAirports(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowAirlines(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowArtPoints(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowAirport(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowAirline(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 0));
}

void Program::cleanMenus()
{
    for (Menu menu : menus)
    {
        for (MenuItem *menuItem : menu.getActions())
        {
            delete menuItem;
        }
    }
}
