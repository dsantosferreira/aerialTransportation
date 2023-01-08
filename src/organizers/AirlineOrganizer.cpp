#include <limits>
#include "AirlineOrganizer.h"
#include "../Database.h"

/** Constructor of AirlineOrganizer, pushes into a vector of strings the possible ways of ordering the values and to a vector of lambda functions the
 * respective lambda functions to order the airlines
 * @brief Constructor of AirlineOrganizer a class that extends Organizer
 */
AirlineOrganizer::AirlineOrganizer()
{
    buttons.push_back("Airline name (Ascendant)");
    buttons.push_back("Airline name (Descendant)");
    buttons.push_back("Airline code (Ascendant)");
    buttons.push_back("Airline code (Descendant)");
    functions.push_back([](Airline a1, Airline a2){ return a1.getName() < a2.getName(); });
    functions.push_back([](Airline a1, Airline a2){ return a1.getName() > a2.getName(); });
    functions.push_back([](Airline a1, Airline a2){ return a1.getCode() < a2.getCode(); });
    functions.push_back([](Airline a1, Airline a2){ return a1.getCode() > a2.getCode(); });
}

/**Draws a table with different order options and sorts the Airlines in different ways depending of the users input. This is done with the use of a vector
 * of lambda functions
 * @brief Organizes the Airlines in different ways depending of the users input
 * @see Organizer::draw() const
 * @param edges the airlines
 * complexity O(N * log(N)) being N the number of airlines
 */
void AirlineOrganizer::organize(vector<Airline> &edges) const
{
    draw();
    string option;
    cout << "\033[32mChoose a way of sorting the results: ";
    cin >> option;
    while (option.length() > 1 or (option[0] < 49 or option[0] > 52))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\033[31m Invalid input! Please choose a valid input: \033[0m";
        cin >> option;
    }
    int c = option[0] - 48 - 1;
    sort(edges.begin(), edges.end(), functions[c]);
    cout<<"\033[0m";
}
