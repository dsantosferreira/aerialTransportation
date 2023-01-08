#ifndef AERIALTRANSPORTATION_MENUITEM_H
#define AERIALTRANSPORTATION_MENUITEM_H

#include "../Database.h"

using namespace std;

class MenuItem
{
protected:
    /** @var menu we are currently in*/
    int *currMenuPage;
    /** @var pointer to the program's database*/
    Database *database;

public:
    MenuItem(int &currMenuPage, Database &database);
    virtual void execute() = 0;
};

#endif
