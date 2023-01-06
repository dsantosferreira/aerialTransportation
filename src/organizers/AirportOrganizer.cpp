//
// Created by franciscocardoso on 03-01-2023.
//

#include <limits>
#include "AirportOrganizer.h"
/** Constructor of AirportOrganizer, pushes into a vector os strings the possible ways of ordering the values and to a vector os lambda functions the
 * respective lambda functions to order the values
 * @brief Constructor of AirportOrganizer a class that extends Organizer
 */
AirportOrganizer::AirportOrganizer() {
    buttons.push_back("Airport name (Ascendant)");
    buttons.push_back("Airport name (Descendant)");
    buttons.push_back("Airport code (Ascendant)");
    buttons.push_back("Airport code (Descendant)");
    buttons.push_back("Airport country name (Ascendant)");
    buttons.push_back("Airport country name (Descendant)");
    buttons.push_back("Airport city name (Ascendant)");
    buttons.push_back("Airport city name (Descendant)");
    functions.push_back([](Airport a1, Airport a2){ return a1.getName() < a2.getName(); });
    functions.push_back([](Airport a1, Airport a2){ return a1.getName() > a2.getName(); });
    functions.push_back([](Airport a1, Airport a2){ return a1.getCode() < a2.getCode(); });
    functions.push_back([](Airport a1, Airport a2){ return a1.getCode() > a2.getCode(); });
    functions.push_back([](Airport a1, Airport a2){ return a1.getCountry() < a2.getCountry(); });
    functions.push_back([](Airport a1, Airport a2){ return a1.getCountry() > a2.getCountry(); });
    functions.push_back([](Airport a1, Airport a2){ return a1.getCity() < a2.getCity(); });
    functions.push_back([](Airport a1, Airport a2){ return a1.getCity() > a2.getCity(); });
}
/**Draws a table with different order options and sorts the Airports in different ways depending of the users input, this is done with the use a vector
 * of lambda functions
 * @brief organizes the Airports in different ways depending of the users input
 * @see Organizer::draw() const
 * @param edges the Airports
 * complexity O(N.log(N)) being N the number of Airports
 */
void AirportOrganizer::organize(vector<Airport> &edges) const
{
    draw();
    string option;
    cout << "Choose a way of sorting the results: ";
    cin >> option;
    while (option.length() > 1 or (option[0] < 49 or option[0] > 56))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[31m Invalid input! Please choose a valid input: \033[0m";
        cin >> option;
    }
    int c = option[0] - 48 - 1;
    sort(edges.begin(), edges.end(), functions[c]);
}
