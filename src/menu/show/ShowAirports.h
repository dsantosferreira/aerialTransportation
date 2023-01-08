#ifndef AERIALTRANSPORTATION_SHOWAIRPORTS_H
#define AERIALTRANSPORTATION_SHOWAIRPORTS_H

using namespace std;
#include "Show.h"

class ShowAirports : public Show
{
public:
    ShowAirports(int &currMenuPage, Database &database);
    void execute() override;
};

#endif // AERIALTRANSPORTATION_SHOWAIRPORTS_H
