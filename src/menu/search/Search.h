#ifndef AERIALTRANSPORTATION_SEARCH_H
#define AERIALTRANSPORTATION_SEARCH_H

#include <limits>
#include "../MenuItem.h"

using namespace std;

typedef vector<list<pair<string, string>>> trips;

class Search : public MenuItem{
private:
    pair<unordered_set<string>, bool> chooseAirports();
    unordered_set<string> chooseAirlines();
    int selectMaximumAirlines();
    trips getMinimalFlights(unordered_set<string> originAirports, unordered_set<string> destAirports, unordered_set<string> airlines, const int maxFlights);
    void draw(int page, list<pair<string, string>> minimalTrip, int nPages) const;
    void paginationController(trips minimalFlights) const;

public:
    Search(int& currMenuPage, Database& database);
    void execute() override;
};

#endif //AERIALTRANSPORTATION_SEARCH_H
