#include "Airport.h"

using namespace std;

/**
 * @brief Constructor of the Airport
 * @param code the code of the airport
 * @param name the name of the airport
 * @param city  the city where the airport is
 * @param country the country where the airport is
 * @param latitude the latitude of the airport's location
 * @param longitude  the longitude of the airport's location
 */

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude) : coordinate(Coordinate(latitude, longitude))
{
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
}

/**
 * Default constructor of Airport, only uses the code of the airport
 * @param code code of the airport
 */
Airport::Airport(string code) : coordinate(Coordinate(0, 0))
{
    this->code = code;
    this->name = "";
    this->city = "";
    this->country = "";
}

/**
 * @return the code of the airport
 */
string Airport::getCode() const
{
    return code;
}

/**
 * @return the name of the airport
 */
string Airport::getName() const
{
    return name;
}

/**
 * @return the country of the airport
 */
string Airport::getCountry() const
{
    return country;
}

/**
 * @return the city of the airport
 */
string Airport::getCity() const
{
    return city;
}

/**
 * @return the coordinates of the airport
 */
Coordinate Airport::getCoordinate() const
{
    return coordinate;
}

/**
 * @brief Prints the code and the name of the airport
 * complexity O(1)
 */
void Airport::print() const
{
    cout << this->getCode() << "       | " << this->getName();
    for (int i = 0; i < 66 - this->getName().length(); i++)
        cout << " ";
}