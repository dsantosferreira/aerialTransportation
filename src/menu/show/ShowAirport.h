//
// Created by franciscocardoso on 07-01-2023.
//

#ifndef AERIALTRANSPORTATION_SHOWAIRPORT_H
#define AERIALTRANSPORTATION_SHOWAIRPORT_H


#include "../../Database.h"
#include "../MenuItem.h"

class ShowAirport: public MenuItem {
public:
    ShowAirport(int &currMenuPage, Database &database1);
    void execute() override ;
};


#endif //AERIALTRANSPORTATION_SHOWAIRPORT_H
