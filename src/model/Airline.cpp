#include "Airline.h"

/**
 * @brief Constructor of Airline
 * @param code the code of the airline
 * @param name the name of the airline
 * @param callSign the callSign of the airline
 * @param country the country of the airline
 */
Airline::Airline(string code, string name, string callSign, string country)
{
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
}

/**
 * Default constructor of the Airline, only receives the code
 * @param code code of the airline
 */
Airline::Airline(string code)
{
    this->code = code;
    this->name = "";
    this->callSign = "";
    this->country = "";
}

/**
 * @return the code of the airline (string)
 */
string Airline::getCode() const
{
    return code;
}

/**
 * @return the name of the airline (string)
 */
string Airline::getName() const
{
    return name;
}

/**
 * @brief prints the code and name of the airline
 * complexity O(1)
 */
void Airline::print() const
{
    cout << this->getCode() << "       | " << this->getName();
    for (int i = 0; i < 66 - this->getName().length(); i++)
        cout << " ";
}