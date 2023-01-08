//
// Created by franciscocardoso on 02-01-2023.
//

#ifndef AERIALTRANSPORTATION_DIRECTFLIGHTS_H
#define AERIALTRANSPORTATION_DIRECTFLIGHTS_H

#include "../MenuItem.h"

class DirectFlights : public MenuItem
{
private:
    /** @var vector of direct flights*/
    vector<Graph::Edge> edges;

public:
    DirectFlights(int &currMenuPage, Database &database);
    void execute() override;
    void draw(int page, int nAirlines,int nAirports, int nCountries, int nCities,int nPages) const;
    void paginationController(int nAirlines,int nAirports, int nCountries, int nCities);
    void getData(set<string> &countries, set<string> &airlines, set<string> &airports, set<pair<string, string>>& cities);
};

#endif // AERIALTRANSPORTATION_DIRECTFLIGHTS_H
