//
// Created by franciscocardoso on 02-01-2023.
//

#include <set>
#include "DirectFlights.h"
#include "../../organizers/DirectFlightsOrganizer.h"
#include <stdlib.h>
#include <limits>

using namespace std;

DirectFlights::DirectFlights(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

void DirectFlights::execute()
{
    system("clear");
    set<string> countries;
    set<string> airlines;
    set<string> airports;
    set<pair<string, string>> cities;
    edges.clear();
    string airport_code;
    int c = 0;
    cout << "Introduce the airport code: ";
    cin >> airport_code;
    if ((database.getFlightsGraph().getNodes().find(airport_code)) != database.getFlightsGraph().getNodes().end())
    {
        Graph::Node airport = (database.getFlightsGraph().getNodes().find(airport_code))->second;
        for (auto e : airport.adj)
        {
            edges.push_back(e);
            string country = database.getAirports().find(Airport(e.destCode, "", "", "", 0, 0))->getCountry();
            string city = database.getAirports().find(Airport(e.destCode, "", "", "", 0, 0))->getCity();
            airlines.insert(e.airlineCode);
            airports.insert(e.destCode);
            countries.insert(country);
            cities.insert(pair(country, city));
            c++;
        }
        DirectFlightsOrganizer organizer(database);
        organizer.organize(edges, database);
        int page = 0;
        while (page >= 0 and page < (float)edges.size() / 10.0)
        {
            string option;
            draw(page, countries, airlines, airports, cities);
            bool cond = true;
            while (cond)
            {
                cond = false;
                cin >> option;
                if (option.length() == 1)
                {
                    switch (option[0])
                    {
                    case '1':
                        page++;
                        break;
                    case '2':
                        page--;
                        break;
                    case '3':
                        page = -1;
                        break;
                    default:
                        cond = true;
                    }
                }
                else
                    cond = true;
                if (cond)
                    cout << "\033[31mInvalid input! Please enter a valid input: \033[0m";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    else
    {
        cout << "\033[31m"
             << "Airport not found!"
             << "\033[0m" << endl;
        cout << "Enter anything to go back: ";
        cin >> airport_code;
    }
}

void DirectFlights::draw(int page, set<string> countries, set<string> airlines, set<string> airports, set<pair<string, string>> cities) const
{
    system("clear");
    cout << " _____________________________________________________________________________________" << endl;
    cout << "|\033[40m                                    Direct flights                                   \033[0m|" << endl;
    cout << "|\033[40m-------------------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m                                       Page " << page + 1;
    for (int i = 0; i < 3 - to_string(page + 1).length(); i++)
        cout << ' ';
    cout << "                                      \033[0m|" << endl;
    cout << "|\033[40m-------------------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m Airlines                | Destination (Airport-Country-City)                        \033[0m|" << endl;
    cout << "|\033[40m_____________________________________________________________________________________\033[0m|" << endl;
    for (int i = 10 * page; i < 10 * page + 10; i++)
    {
        if (i == edges.size())
            break;
        Graph::Edge e = edges[i];
        string country = database.getAirports().find(Airport(e.destCode, "", "", "", 0, 0))->getCountry();
        string city = database.getAirports().find(Airport(e.destCode, "", "", "", 0, 0))->getCity();
        cout << "|";
        if (i % 2 == 0)
            cout << "\033[47m"
                 << "\033[30m";
        else
            cout << "\033[100m";
        cout << " " << e.airlineCode << "                     | " << e.destCode << '-' << country << '-' << city;
        for (int i = 0; i < 53 - country.length() - city.length(); i++)
            cout << " ";
        cout << "\033[0m"
             << "|" << endl;
    }

    cout << "|\033[100m_____________________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m Airlines:" << airlines.size();
    for (int i = 0; i < 10 - to_string(airlines.size()).length(); i++)
        cout << ' ';
    cout << "| Airports:" << airports.size();
    for (int i = 0; i < 11 - to_string(airports.size()).length(); i++)
        cout << ' ';
    cout << "| Countries:" << countries.size();
    for (int i = 0; i < 11 - to_string(countries.size()).length(); i++)
        cout << ' ';
    cout << "| Cities:" << cities.size();
    for (int i = 0; i < 11 - to_string(cities.size()).length(); i++)
        cout << ' ';
    cout << "\033[0m|" << endl;
    cout << "|\033[40m_____________________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m [1]Next                   [2]Previous                   [3]Go Back                  \033[0m|" << endl;
    cout << "|\033[40m_____________________________________________________________________________________\033[0m|" << endl;
    cout << endl
         << "Choose an option: ";
}
