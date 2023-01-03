//
// Created by franciscocardoso on 02-01-2023.
//

#ifndef AERIALTRANSPORTATION_DIRECTFLIGHTS_H
#define AERIALTRANSPORTATION_DIRECTFLIGHTS_H

#include "../MenuItem.h"

class DirectFlights : public MenuItem
{
private:
    Database database;
    vector<Graph::Edge> edges;

public:
    DirectFlights(int &currMenuPage, Database &database);
    void execute() override;
    void draw(int page, set<string> countries, set<string> airlines, set<string> airports, set<pair<string, string>> cities) const;
};

#endif // AERIALTRANSPORTATION_DIRECTFLIGHTS_H
