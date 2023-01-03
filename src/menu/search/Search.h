#ifndef AERIALTRANSPORTATION_SEARCH_H
#define AERIALTRANSPORTATION_SEARCH_H

#include <limits>
#include "../MenuItem.h"

using namespace std;

typedef vector<list<pair<string, string>>> trips;

class Search : public MenuItem{
private:
    vector<string> readMenuButtons();
    void drawMenu(vector<string> buttons);
    unordered_set<string> chooseAirports();
    unordered_set<string> chooseAirlines();
    trips getMinimalFlights(unordered_set<string> originAirports, unordered_set<string> destAirports, unordered_set<string> airlines);
    void printMinimalFlights(trips minimalflights);
public:
    Search(int& currMenuPage, Database& database);
    void execute() override;
};

#endif //AERIALTRANSPORTATION_SEARCH_H
