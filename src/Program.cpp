#include <limits>
#include <set>
#include "Program.h"
#include "menu/show/ShowAirport.h"
#include "menu/show/ShowAirline.h"
#include "menu/search/DirectFlights.h"
#include "menu/search/ReachableDestinations.h"
#include "menu/statistics/Statistics.h"

/**
 * Program's constructor responsible for initializing the database and the menus
 * @brief Program's constructor
 */
Program::Program()
{
    currMenuPage = 0;
    database = Database();
    createMainMenu();
    createMenu1();
    createShowMenu();
}

/**
 * @brief Keeps the program running while the user doesn't leave the main menu. Makes the mnu perform the action according to the user's inserted option
 */
void Program::run()
{
    int option;
    while (currMenuPage != -1)
    {
        menus[currMenuPage].draw();

        cout << "\033[32mInsert an option: ";
        while (getMenuOption(option, menus[currMenuPage].getButtons().size()))
            cout << "\033[31mPlease insert a valid option: \033[0m";
        cout<<"\033[0m";
        Menu menu = menus[currMenuPage];
        menu.doAction(option - 1);
    }

    cleanMenus();
}

/**
 * @brief Tries to read the user's input for the menu option
 * @param option variable that will store the option
 * @param nButtons number of buttons on the current menu
 * @return true if the input provided wasn't in the right format, false otherwise
 */
bool Program::getMenuOption(int &option, int nButtons)
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

/**
 * @brief Creates the main menu
 */
void Program::createMainMenu()
{
    menus.push_back(Menu("../files/mainMenu"));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 1));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 2));
    menus[menus.size() - 1].addMenuItem(new Search(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new Statistics(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, -1));
}

/**
 * @brief Creates menu for the direct flights and reachable destinations
 */
void Program::createMenu1()
{
    menus.push_back(Menu("../files/menu1"));
    menus[menus.size() - 1].addMenuItem(new DirectFlights(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ReachableDestinations(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 0));
}

/**
 * @brief Creates the show menu
 */
void Program::createShowMenu()
{
    menus.push_back(Menu("../files/menu2"));
    menus[menus.size() - 1].addMenuItem(new ShowAirports(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowAirlines(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowArtPoints(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowAirport(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ShowAirline(currMenuPage, database));
    menus[menus.size() - 1].addMenuItem(new ChangeMenu(currMenuPage, database, 0));
}

/**
 * @brief deallocates memory that was allocated for each menuItem in each menu
 * Complexity: O(N*M) being N the number of menus and M the number of menuItems in each menu
 */
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
