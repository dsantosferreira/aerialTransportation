//
// Created by franciscocardoso on 31-12-2022.
//

#include <algorithm>
#include "ShowAirline.h"
#include "../../organizers/AirlineOrganizer.h"
/**
 * @brief Constructor of the ShowAirline, a class that extends Show
 * @param currMenuPage the current page os the menu
 * @param database database that stores all the information
 */
ShowAirline::ShowAirline(int &currMenuPage, Database &database) : Show(currMenuPage, database){};
/**
 * @brief displays all the Airlines
 * @see Show:: draw(vector<Name> data)
 * complexity: O(N) being N the number of airlines
 */
void ShowAirline::execute()
{
    vector<Airline> airports;
    for (Airline airport : database.getAirlines())
        airports.push_back(airport);
    AirlineOrganizer airlineOrganizer;
    airlineOrganizer.organize(airports);
    Show::draw<Airline>(airports);
}