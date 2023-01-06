#ifndef AERIALTRANSPORTATION_SHOWARTPOINTS_H
#define AERIALTRANSPORTATION_SHOWARTPOINTS_H

#include "Show.h"
#include "../../organizers/AirportOrganizer.h"
#include "../../Database.h"

using namespace std;

class ShowArtPoints: public Show {
public:
    ShowArtPoints(int &currMenuPage, Database &database);
    void execute() override;
    unordered_set<string> chooseAirlines();
};


#endif //AERIALTRANSPORTATION_SHOWARTPOINTS_H
