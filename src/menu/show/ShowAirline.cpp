//
// Created by franciscocardoso on 31-12-2022.
//

#include <algorithm>
#include "ShowAirline.h"
#include "../../organizers/AirlineOrganizer.h"

ShowAirline::ShowAirline(int &currMenuPage, Database &database) : Show(currMenuPage, database){};

void ShowAirline::execute()
{
    vector<Airline> airports;
    for (Airline airport : database.getAirlines())
        airports.push_back(airport);
    AirlineOrganizer airlineOrganizer;
    airlineOrganizer.organize(airports);
    Show::draw<Airline>(airports);
}