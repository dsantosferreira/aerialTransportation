#ifndef AERIALTRANSPORTATION_SEARCH_H
#define AERIALTRANSPORTATION_SEARCH_H

#include <limits>
#include <algorithm>
#include <iomanip>
#include "../MenuItem.h"

using namespace std;

typedef vector<pair<list<pair<string, string>>, float>> trips;
typedef pair<list<pair<string, string>>, float> trip;

class Search : public MenuItem{
private:
    unordered_set<string> airportInput(Database& database);
    unordered_set<string> cityInput(Database& database);
    unordered_set<string> locationInput(Database& database);
    bool getMaximumAirlines(int &maxAirlines);
    pair<unordered_set<string>, bool> chooseAirports();
    unordered_set<string> chooseAirlines();
    int selectMaximumAirlines();
    void draw(int page, trip minimalTrip, int nPages) const;
    void paginationController(trips minimalFlights) const;

public:
    Search(int& currMenuPage, Database& database);
    void execute() override;
};

#endif
