#ifndef AERIALTRANSPORTATION_SHOWAIRLINE_H
#define AERIALTRANSPORTATION_SHOWAIRLINE_H


#include "../../Database.h"
#include "../MenuItem.h"

class ShowAirline: public MenuItem{
public:
    ShowAirline(int &currMenuPage, Database &database);
    void execute() override;
};


#endif //AERIALTRANSPORTATION_SHOWAIRLINE_H
