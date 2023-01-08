//
// Created by franciscocardoso on 31-12-2022.
//

#include <algorithm>
#include "ShowAirports.h"
#include "../../organizers/AirportOrganizer.h"
/**
 * @brief Constructor of the ShowAirports, a class that extends Show
 * @param currMenuPage the current page os the menu
 * @param database database that stores all the information
 */
ShowAirports::ShowAirports(int &currMenuPage, Database &database) : Show(currMenuPage, database){};
/**
 * @brief displays all the Airports
 * @see Show:: paginationController(vector<Name> data)
 * complexity: O(N) being N the number of airports
 */
void ShowAirports::execute()
{
    vector<Airport> airports;
    for (Airport airport : database.getAirports())
        airports.push_back(airport);
    AirportOrganizer airportOrganizer;
    airportOrganizer.organize(airports);
    paginationController(airports);
}