#include <algorithm>
#include "ShowAirlines.h"
#include "../../organizers/AirlineOrganizer.h"
/**
 * @brief Constructor of the ShowAirlines, a class that extends Show
 * @param currMenuPage the current page os the menu
 * @param database database that stores all the information
 */
ShowAirlines::ShowAirlines(int &currMenuPage, Database &database) : Show(currMenuPage, database){};
/**
 * @brief displays all the Airlines
 * @see Show:: paginationController(vector<Name> data)
 * complexity: O(N log(N)) being N the number of airlines
 */
void ShowAirlines::execute()
{
    vector<Airline> airlines;
    for (Airline airline : database->getAirlines())
        airlines.push_back(airline);
    AirlineOrganizer airlineOrganizer;
    airlineOrganizer.organize(airlines);
    paginationController(airlines);
}