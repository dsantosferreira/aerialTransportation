#ifndef AERIALTRANSPORTATION_STATISTICS_H
#define AERIALTRANSPORTATION_STATISTICS_H

#include "../MenuItem.h"

class Statistics : public MenuItem{
private:
public:
    Statistics(int& currMenuPage, Database& database);
    void execute();

    int diameter(unordered_set<string> airlines, unordered_set<string> countries);

    vector<Airport> topAirportFlights(unordered_set<string> airlines, unordered_set<string> countries);

    vector<Airport> topAirportAirlines(unordered_set<string> airlines, unordered_set<string> countries);
};

#endif //AERIALTRANSPORTATION_STATISTICS_H
