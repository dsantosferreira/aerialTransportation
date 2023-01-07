//
// Created by franciscocardoso on 04-01-2023.
//

#include <limits>
#include <cmath>
#include "ReachableDestinations.h"
#include "../../organizers/AirportOrganizer.h"

/*** Constructs a ReachableDestinations, a class that extends the MenuItem class
 * @param currpage
 * @param database
 */
ReachableDestinations::ReachableDestinations(int &currpage, Database database) : MenuItem(currpage,database){}

/**This function makes the search for reachable locations from an airport with a max number of flights more user friendly, as it ask for the user inputs
 * orders the obtain results and displays them in a more pleasant and organize way.
 * @brief interacts with the user and makes the search for reachable locations from an airport with a max number of flights more user friendly
 * @see ReachableDestinations::draw(int page, int nCountries,int nCities)
 * @see ReachableDestinations:: paginationController(int nCountries,int nCities)const
 * @see Graph::reachedAirportsBFS(int maxFlights, string original)
 * complexity: O(E+V) being V the number of nodes, E the number of edges
 */
void ReachableDestinations::execute() {
    int n;
    string original;
    cout<< "\033[32mInsert the airport: ";
    cin>>original;
    if(database.getAirports().find(original)==database.getAirports().end()){
        cout<<"\033[31mAirport not found!\033[0m"<<endl;
        cout<<"\033[32mEnter anything to go back: ";
        cin>>original;
    }
    else{
        while(true){
            cout<<"\033[32mEnter the max numbers of flights: ";
            cin>>n;
            if(cin.fail()){
                cout<<"\033[31mInvalid input!\033[0m"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if(n<1) cout<<"\003[31mInvalid input! Number should be greater than 1!\033[31m"<<endl;
            else{
                break;
            }
        }
        set<string> countries;
        set<pair<string,string>> cities;
        set<string> aux=database.getFlightsGraph().reachedAirportsBFS(n,original);
        for(string s: aux){
            Airport airport=database.getAirport(s);
            edges.push_back(airport);
            countries.insert(airport.getCountry());
            cities.insert(pair(airport.getCountry(),airport.getCity()));
        }
        AirportOrganizer airportOrganizer;
        airportOrganizer.organize(edges);
        paginationController(countries.size(),cities.size());

    }
}
/**Draws a table where it displays the reachable locations, it makes use of a system of pagination where only displays 10 locations in each page
 * @brief draws a table where it displays the reachable locations
 * @param page current page
 * @param nCountries number of countries reached
 * @param nCities  number of cities reached
 * @param npages number of pages
 * complexity: O(1)
 */
void ReachableDestinations::draw(int page, int nCountries,int nCities,int npages) const
{
    system("clear");
    cout<<"\033[0m";
    cout <<         " _______________________________________________________________" << endl;
    cout << "|\033[40m                     Reachable Destinations                    \033[0m|" << endl;
    cout << "|\033[40m---------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m                           Page ("<<page +1<<"/"<<npages<<")";
    for (int i = 0; i < 8 - to_string(page + 1).length()- to_string(npages).length(); i++)
        cout << ' ';
    cout << "                    \033[0m|" << endl;
    cout << "|\033[40m---------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m Destination (Airport-Country-City)                            \033[0m|" << endl;
    cout << "|\033[40m_______________________________________________________________\033[0m|" << endl;
    for (int i = 10 * page; i < 10 * page + 10; i++)
    {
        if (i == edges.size())
            break;
        Airport e = edges[i];
        cout << "|";
        if (i % 2 == 0)
            cout << "\033[47m"
                 << "\033[30m";
        else
            cout << "\033[100m";
        cout  << e.getCode() << " - " << e.getCountry() << " - " << e.getCity();
        for (int i = 0; i < 54 - e.getCountry().length() - e.getCity().length(); i++)
            cout << " ";
        cout << "\033[0m"
             << "|" << endl;
    }
    cout << "|\033[100m_______________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m  Airports:" << edges.size();
    for (int i = 0; i < 10 - to_string(edges.size()).length(); i++)
        cout << ' ';
    cout << "| Countries:" << nCountries;
    for (int i = 0; i < 10 - to_string(nCountries).length(); i++)
        cout << ' ';
    cout << "| Cities:" << nCities;
    for (int i = 0; i <11 - to_string(nCities).length(); i++)
        cout << ' ';
    cout << "\033[0m|" << endl;
    cout << "|\033[40m_______________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m [n]Next             [p]Previous             [q]Go Back        \033[0m|" << endl;
    cout << "|\033[40m_______________________________________________________________\033[0m|" << endl;


}
/** Controls the pagination of the drawn table. it ask the user for an input and decides if it as to go to the next page, the previous or go back to the menu
 * @brief Controls the pagination of the drawn table.
 * @see ReachableDestinations::draw(int page, int nCountries, int nCities) const
 * @param nCountries number of countries reached
 * @param nCities  number of cities reached
 * complexity: O(1)
 */
void ReachableDestinations:: paginationController(int nCountries,int nCities)const{
    int page = 0;
    while (page >= 0 and page < (float)edges.size() / 10.0)
    {
        string option;
        draw( page,  nCountries, nCities,ceil((float)edges.size()/10.0));
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
                cout << "\033[31mInvalid input! Please enter a valid input: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

