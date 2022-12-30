#ifndef AERIALTRANSPORTATION_DATABASE_H
#define AERIALTRANSPORTATION_DATABASE_H

#include <unordered_set>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;

struct airportHash {
    int operator() (const Airport& airport) const {
        int hash = 0;
        string airportCode = airport.getCode();
        for (int i = 0; i < airportCode.size(); i++) {
            hash += airportCode[i] * i;
        }
        return hash % 3023;
    }

    bool operator() (const Airport& airport1, const Airport& airport2) const {
        return airport1.getCode() == airport2.getCode();
    }
};

struct airlineHash {
    int operator() (const Airline& airline) const {
        int hash = 0;
        string airlineCode = airline.getCode();
        for (int i = 0; i < airlineCode.size(); i++) {
            hash += airlineCode[i] * i;
        }
        return hash % 449;
    }

    bool operator() (const Airline& airline1, const Airline& airline2) const {
        return airline1.getCode() == airline2.getCode();
    }
};

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
