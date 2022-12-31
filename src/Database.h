#ifndef AERIALTRANSPORTATION_DATABASE_H
#define AERIALTRANSPORTATION_DATABASE_H

#include <unordered_set>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

typedef unordered_set<Airport, airportHash, airportHash> airportHTable;
typedef unordered_set<Airline, airlineHash, airlineHash> airlineHTable;

class Database {
private:
    airportHTable airports;
    airlineHTable airlines;
    //Graph flights;

public:
    Database();
    airportHTable getAirports() const;
    airlineHTable getAirlines() const;
};


#endif
