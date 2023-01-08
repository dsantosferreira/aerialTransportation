#ifndef AERIALTRANSPORTATION_AIRPORTORGANIZER_H
#define AERIALTRANSPORTATION_AIRPORTORGANIZER_H


#include "Organizer.h"

class AirportOrganizer: public Organizer
{
    private:
    /** @var Vector of functions to be used to sort airports*/
    vector<function<bool(Airport,Airport)>> functions;
    public:
    AirportOrganizer();
    void organize(vector<Airport> &airports) const;
};



#endif //AERIALTRANSPORTATION_AIRPORTORGANIZER_H
