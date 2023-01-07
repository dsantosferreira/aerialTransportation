//
// Created by franciscocardoso on 02-01-2023.
//

#include <set>
#include "DirectFlights.h"
#include "../../organizers/DirectFlightsOrganizer.h"
#include <stdlib.h>
#include <limits>
#include <cmath>

using namespace std;
/**
 * @brief Constructor of DirectFlights a class that extends MenuItem.
 * @param currMenuPage The current page of the menu
 * @param database the database we are using to store the data
 */
DirectFlights::DirectFlights(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

/**This function makes the search for the direct flights from an airport more user friendly, as it ask for the user inputs,orders the obtain results
 * and displays them in a more pleasant and organize way.
 * @brief interacts with the user and makes the search for the direct flights from an airport more user friendly more user friendly.
 * @see DirectFlights::draw(int page, int nAirlines,int nAirports, int nCountries, int nCities) const
 * @see DirectFlights::paginationController(int nAirlines,int nAirports, int nCountries, int nCities)
 * @see Graph::getEdges( string node)
 * @see DirectFlights::getData(set<string>& countries, set<string>& airlines, set<string> &airports,set<pair<string, string>>& cities)
 * complexity: O(E) being E the number of edges.
 */
void DirectFlights::execute()
{
    system("clear");
    cout<<"\033[0m";
    set<string> countries;
    set<string> airlines;
    set<string> airports;
    set<pair<string, string>> cities;
    edges.clear();
    string airport_code;
    int c = 0;
    cout << "\033[32mIntroduce the airport code: ";
    cin >> airport_code;
    if ((database.getFlightsGraph().getNodes().find(airport_code)) != database.getFlightsGraph().getNodes().end())
    {
        edges=database.getFlightsGraph().getEdges(airport_code);
        DirectFlightsOrganizer organizer(database);
        organizer.organize(edges, database);
        getData(countries,airlines,airports,cities);
        paginationController(airlines.size(),airports.size(),countries.size(),cities.size());
    }
    else
    {
        cout << "\033[31m"
             << "Airport not found!"
             << "\033[0m" << endl;
        cout << "\033[32mEnter anything to go back: ";
        cin >> airport_code;
    }
}
/**Draws a table where it displays the direct flights, it makes use of a system of pagination where only displays 10 locations in each page
* @brief draws a table where it displays the direct flights of an airport.
 * @param page current page
 * @param nAirlines number of possible airlines to use
 * @param nAirports number of possible airports to go
 * @param nCountries number of possible countries to go
 * @param nCities  number of possible cities to go
 * @param npages the number of pages
 * complexity: O(1)
 */
void DirectFlights::draw(int page, int nAirlines,int nAirports, int nCountries, int nCities,int npages) const
{
    system("clear");
    cout<<"\033[0m";
    cout << " ____________________________________________________________________________" << endl;
    cout << "|\033[40m                               Direct flights                               \033[0m|" << endl;
    cout << "|\033[40m----------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m                                  Page(" << page + 1<<"/"<<npages<<")";
    for (int i = 0; i < 8 - to_string(page + 1).length()- to_string(npages).length(); i++)
        cout << ' ';

    cout << "                           \033[0m|" << endl;
    cout << "|\033[40m----------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m Airlines   | Destination (Airport-Country-City)                            \033[0m|" << endl;
    cout << "|\033[40m____________________________________________________________________________\033[0m|" << endl;
    for (int i = 10 * page; i < 10 * page + 10; i++)
    {
        if (i == edges.size())
            break;
        Graph::Edge e = edges[i];
        string country = database.getAirport(e.destCode).getCountry();
        string city = database.getAirport(e.destCode).getCity();
        cout << "|";
        if (i % 2 == 0)
            cout << "\033[47m"
                 << "\033[30m";
        else
            cout << "\033[100m";
        cout << " " << e.airlineCode << "        | " << e.destCode << " - " << country << " - " << city;
        for (int i = 0; i < 53 - country.length() - city.length(); i++)
            cout << " ";
        cout << "\033[0m"
             << "|" << endl;
    }

    cout << "|\033[100m____________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m Airlines:" << nAirlines;
    for (int i = 0; i < 8 - to_string(nAirlines).length(); i++)
        cout << ' ';
    cout << "| Airports:" << nAirports;
    for (int i = 0; i < 9 - to_string(nAirports).length(); i++)
        cout << ' ';
    cout << "| Countries:" << nCountries;
    for (int i = 0; i < 8 - to_string(nCountries).length(); i++)
        cout << ' ';
    cout << "| Cities:" << nCities;
    for (int i = 0; i < 9 - to_string(nCities).length(); i++)
        cout << ' ';
    cout << "\033[0m|" << endl;
    cout << "|\033[40m____________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m [n]Next                [p]Previous                [q]Go Back               \033[0m|" << endl;
    cout << "|\033[40m____________________________________________________________________________\033[0m|" << endl;

}
/**
 * @brief gets the variety of countries, cities and airports reached as well as the number of airlines available at the airport
 * @param countries a set of strings
 * @param airlines a set of strings
 * @param airports a set of strings
 * @param cities a set of strings
 * complexity O(E) being E the number of Direct flights
 */
void DirectFlights::getData(set<string>& countries, set<string>& airlines, set<string> &airports,set<pair<string, string>>& cities) {
    for(auto e: edges){
        airlines.insert(e.airlineCode);
        Airport airport= database.getAirport(e.destCode);
        countries.insert(airport.getCountry());
        cities.insert(pair(airport.getCountry(),airport.getCity()));
        airports.insert(e.destCode);
    }
}
/** Controls the pagination of the drawn table. it ask the user for an input and decides if it as to go to the next page, the previous or go back to the menu
* @brief Controls the pagination of the drawn table.
* @see DirectFlights::draw(int page, int nAirlines,int nAirports, int nCountries, int nCities) const
* @param nAirlines number of possible airlines to use
* @param nAirports number of possible airports to go
* @param nCountries number of possible countries to go
* @param nCities  number of possible cities to go
* complexity: O(1)
  */
void DirectFlights::paginationController(int nAirlines,int nAirports, int nCountries, int nCities) {
    int page = 0;
    while (page >= 0 and page < (float)edges.size() / 10.0)
    {
        string option;
        draw(page, nAirlines, nAirports, nCountries, nCities,ceil((float)edges.size()/10.0));
        bool cond = true;
        while (cond)
        {
            cout << endl
                 << "\033[32mChoose an option[n/p/q] or the number of the page you would want to go[1-"<<ceil((float)edges.size()/10.0)<<"]: ";
            cond = true;
            cin >> option;

            if (option.length() == 1)
            {
                option= ::toupper(option[0]);
                switch (option[0])
                {
                    case 'N':
                        page++;
                        cond=false;
                        break;
                    case 'P':
                        page--;
                        cond=false;
                        break;
                    case 'Q':
                        page = -1;
                        cond=false;
                        break;
                    default:
                        cond = true;
                }
            }
            if(cond){
                int test;
                try{
                    cond=false;
                     test= stoi(option);
                }catch (invalid_argument){
                    cond=true;
                }
                if(!cond){
                    cond=true;
                    if(to_string(test).length()==option.length()){
                        if(test>0 and test <=ceil((float)edges.size()/10.0)) {
                            page=test-1;
                            cond= false;
                        }
                    }

                }
            }
            if (cond)
                cout << "\033[31mInvalid input! Please enter a valid input! \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
