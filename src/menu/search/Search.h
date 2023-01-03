#ifndef AERIALTRANSPORTATION_SEARCH_H
#define AERIALTRANSPORTATION_SEARCH_H

#include <limits>
#include "../MenuItem.h"

using namespace std;

class Search : public MenuItem{
private:
    vector<string> readMenuButtons();
    void drawMenu(vector<string> buttons);
    unordered_set<string> chooseAirports();
    unordered_set<string> chooseAirlines();
public:
    Search(int& currMenuPage, Database& database);
    void execute();
};

#endif //AERIALTRANSPORTATION_SEARCH_H
