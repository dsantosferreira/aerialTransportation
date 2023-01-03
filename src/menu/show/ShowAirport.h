//
// Created by franciscocardoso on 31-12-2022.
//

#ifndef AERIALTRANSPORTATION_SHOWAIRPORT_H
#define AERIALTRANSPORTATION_SHOWAIRPORT_H

using namespace std;
#include "Show.h"

class ShowAirport : public Show
{
public:
    ShowAirport(int &currMenuPage, Database &database);
    void execute() override;
};

#endif // AERIALTRANSPORTATION_SHOWAIRPORT_H
