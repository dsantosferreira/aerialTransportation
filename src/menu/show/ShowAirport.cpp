//
// Created by franciscocardoso on 31-12-2022.
//

#include <algorithm>
#include "ShowAirport.h"


ShowAirport::ShowAirport(int &currMenuPage, Database &database): Show(currMenuPage, database) {};


void ShowAirport::execute() {
    vector<Airport> airports;
    for( Airport airport: database.getAirports()) airports.push_back(airport);
    sort(airports.begin(), airports.end(),[](Airport a1,Airport a2){return a1.getName()<a2.getName();});
    Show::draw<Airport>(airports);
}
