#ifndef AERIALTRANSPORTATION_STATISTICS_H
#define AERIALTRANSPORTATION_STATISTICS_H

#include "../MenuItem.h"

class Statistics : public MenuItem{
private:
public:
    Statistics(int& currMenuPage, Database& database);
    void execute();

    int diameter(string airline, string country);

    vector<Airport> topAirportFlights(string airline, string country);

    vector<Airport> topAirportAirlines(string airline, string country);
};

#endif //AERIALTRANSPORTATION_STATISTICS_H
