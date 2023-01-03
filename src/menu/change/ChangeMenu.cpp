#include "ChangeMenu.h"

ChangeMenu::ChangeMenu(int &currMenuPage, Database &database, int nextMenu) : MenuItem(currMenuPage, database)
{
    this->nextMenu = nextMenu;
}

void ChangeMenu::execute()
{
    *(this->currMenuPage) = nextMenu;
}