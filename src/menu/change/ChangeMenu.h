#ifndef AERIALTRANSPORTATION_CHANGEMENU_H
#define AERIALTRANSPORTATION_CHANGEMENU_H

#include "../MenuItem.h"

using namespace std;

class ChangeMenu : public MenuItem
{
private:
    /** @var Menu to change to */
    int nextMenu;

public:
    ChangeMenu(int &currMenuPage, Database &database, int nextMenu);
    void execute() override;
};

#endif
