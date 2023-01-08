#ifndef AERIALTRANSPORTATION_AIRLINEORGANIZER_H
#define AERIALTRANSPORTATION_AIRLINEORGANIZER_H
#include "Organizer.h"
#include "../model/Airline.h"
#include "../Database.h"

class AirlineOrganizer : public Organizer
{
private:
    /** @var Vector of functions to be used to sort airlines*/
    vector<function<bool(Airline,Airline)>> functions;
public:
    AirlineOrganizer();
    void organize(vector<Airline> &airlines) const;
};

#endif // AERIALTRANSPORTATION_AIRLINEORGANIZER_H
