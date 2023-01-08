//
// Created by franciscocardoso on 04-01-2023.
//

#ifndef AERIALTRANSPORTATION_REACHABLEDESTINATIONS_H
#define AERIALTRANSPORTATION_REACHABLEDESTINATIONS_H


#include "../MenuItem.h"

using namespace std;

class ReachableDestinations: public MenuItem {
private:
    /** @var vector of flights to reachable places*/
    vector<Airport> edges;
public:
    ReachableDestinations(int& currpage,Database &database);
    void execute() override;
    void draw(int page, int nCountries, int nCities,int nPages) const;
    void paginationController(int nCountries,int nCities)const;
};


#endif //AERIALTRANSPORTATION_REACHABLEDESTINATIONS_H
