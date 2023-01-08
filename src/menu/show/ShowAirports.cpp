#include <algorithm>
#include "ShowAirports.h"
#include "../../organizers/AirportOrganizer.h"

/**
 * @brief Constructor of the ShowAirports, a class that extends Show
 * @param currMenuPage the current page of the menu
 * @param database database that stores all the information
 */
ShowAirports::ShowAirports(int &currMenuPage, Database &database) : Show(currMenuPage, database){};

/**
 * @brief Displays all the Airports
 * @see Show::paginationController(vector<Name> data)
 * Complexity: O(N log(N)) being N the number of airports
 */
void ShowAirports::execute()
{
    vector<Airport> airports;
    for (Airport airport : database->getAirports())
        airports.push_back(airport);
    AirportOrganizer airportOrganizer;
    airportOrganizer.organize(airports);
    paginationController(airports);
}
