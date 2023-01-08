//
// Created by franciscocardoso on 31-12-2022.
//

#ifndef AERIALTRANSPORTATION_SHOWAIRLINES_H
#define AERIALTRANSPORTATION_SHOWAIRLINES_H

#include "Show.h"

class ShowAirlines : public Show
{

public:
    ShowAirlines(int &currMenuPage, Database &database);
    void execute() override;
};

#endif // AERIALTRANSPORTATION_SHOWAIRLINES_H
