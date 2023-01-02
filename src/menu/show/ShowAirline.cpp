//
// Created by franciscocardoso on 31-12-2022.
//

#include <algorithm>
#include "ShowAirline.h"
ShowAirline::ShowAirline(int &currMenuPage, Database &database): Show(currMenuPage, database) {};


void ShowAirline::execute() {
    vector<Airline> airports;
    for( Airline airport: database.getAirlines()) airports.push_back(airport);
    sort(airports.begin(), airports.end(),[](Airline a1,Airline a2){return a1.getName()<a2.getName();});
    Show::draw<Airline>(airports);
}