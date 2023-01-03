#ifndef AERIALTRANSPORTATION_DATABASE_H
#define AERIALTRANSPORTATION_DATABASE_H

#include <unordered_set>
#include <fstream>
#include <sstream>
#include "model/Airport.h"
#include "model/Airline.h"
#include "model/Graph.h"

using namespace std;

typedef unordered_set<Airport, airportHash, airportHash> airportHTable;
typedef unordered_set<Airline, airlineHash, airlineHash> airlineHTable;

class Database
{
private:
    airportHTable airports;
    airlineHTable airlines;
    Graph flights;

public:
    Database();
    airportHTable getAirports() const;
    Airport getAirport(string code) const;
    Airline getAirline(string code) const;
    airlineHTable getAirlines() const;
    Graph getFlightsGraph() const;
    void readAirports();
    void readAirlines();
    void createFlightsGraph();
};

#endif
