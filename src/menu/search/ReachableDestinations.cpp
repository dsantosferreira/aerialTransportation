//
// Created by franciscocardoso on 04-01-2023.
//

#include <limits>
#include "ReachableDestinations.h"
#include "../../organizers/AirportOrganizer.h"

ReachableDestinations::ReachableDestinations(int &currpage, Database database) : MenuItem(currpage,database){}

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
        inputControl(countries.size(),cities.size());

    }
}

void ReachableDestinations::draw(int page, int nCountries,int nCities) const
{
    system("clear");
    cout<<"\033[0m";
    cout <<         " _______________________________________________________________" << endl;
    cout << "|\033[40m                     Reachable Destinations                    \033[0m|" << endl;
    cout << "|\033[40m---------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m                             Page "<<page +1;
    for (int i = 0; i < 3 - to_string(page + 1).length(); i++)
        cout << ' ';
    cout << "                          \033[0m|" << endl;
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
    cout << "|\033[40m [1]Next             [2]Previous             [3]Go Back        \033[0m|" << endl;
    cout << "|\033[40m_______________________________________________________________\033[0m|" << endl;
    cout << endl
         << "\033[32mChoose an option: ";

}

void ReachableDestinations:: inputControl(int nCountries,int nCities)const{
    int page = 0;
    while (page >= 0 and page < (float)edges.size() / 10.0)
    {
        string option;
        draw(page,  nCountries, nCities);
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

