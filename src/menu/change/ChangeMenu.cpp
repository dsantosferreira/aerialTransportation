#include "ChangeMenu.h"
/**
 * Constructor of ChangeMenu a class that extends MenuItem
 * @param currMenuPage  current page of the menu
 * @param database database that stores all the information
 * @param nextMenu the page we want to go next
 */
ChangeMenu::ChangeMenu(int &currMenuPage, Database &database, int nextMenu) : MenuItem(currMenuPage, database)
{
    this->nextMenu = nextMenu;
}
/**
 * @brief changes the current menu page to another page
 * complexity O(1)
 */
void ChangeMenu::execute()
{
    *(this->currMenuPage) = nextMenu;
}