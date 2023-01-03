//
// Created by franciscocardoso on 03-01-2023.
//

#include <limits>
#include "DirectFlightsOrganizer.h"
#include "../Database.h"

DirectFlightsOrganizer::DirectFlightsOrganizer(Database database) : Organizer()
{
    buttons.push_back("Airline name (Ascendant)");
    buttons.push_back("Airline name (Descendant)");
    buttons.push_back("Airport name (Ascendant)");
    buttons.push_back("Airport name (Descendant)");
    buttons.push_back("Country name (Ascendant)");
    buttons.push_back("Country name (Descendant)");
    buttons.push_back("City name (Ascendant)");
    buttons.push_back("City name (Descendant)");
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirline(e1.airlineCode).getName() < database.getAirline(e2.airlineCode).getName(); });
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirline(e1.airlineCode).getName() > database.getAirline(e2.airlineCode).getName(); });
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirport(e1.destCode).getName() < database.getAirport(e2.destCode).getName(); });
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirport(e1.destCode).getName() > database.getAirport(e2.destCode).getName(); });
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirport(e1.destCode).getCountry() < database.getAirport(e2.destCode).getCountry(); });
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirport(e1.destCode).getCountry() > database.getAirport(e2.destCode).getCountry(); });
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirport(e1.destCode).getCity() < database.getAirport(e2.destCode).getCity(); });
    functions.push_back([&database](Graph::Edge e1, Graph::Edge e2){ return database.getAirport(e1.destCode).getCity() > database.getAirport(e2.destCode).getCity(); });
}
void DirectFlightsOrganizer::organize(vector<Graph::Edge> &edges, Database database) const
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
