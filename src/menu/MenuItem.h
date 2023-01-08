#ifndef AERIALTRANSPORTATION_MENUITEM_H
#define AERIALTRANSPORTATION_MENUITEM_H

#include "../Database.h"

using namespace std;

class MenuItem
{
protected:
    int *currMenuPage;
    Database *database;

public:
    MenuItem(int &currMenuPage, Database &database);
    virtual void execute() = 0;
};

#endif
