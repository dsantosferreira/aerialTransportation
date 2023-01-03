//
// Created by franciscocardoso on 31-12-2022.
//

#include <algorithm>
#include "ShowAirport.h"
#include "../../organizers/AirportOrganizer.h"

ShowAirport::ShowAirport(int &currMenuPage, Database &database) : Show(currMenuPage, database){};

void ShowAirport::execute()
{
    vector<Airport> airports;
    for (Airport airport : database.getAirports())
        airports.push_back(airport);
    AirportOrganizer airportOrganizer;
    airportOrganizer.organize(airports);
    Show::draw<Airport>(airports);
}
