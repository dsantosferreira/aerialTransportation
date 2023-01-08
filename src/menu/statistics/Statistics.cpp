#include <algorithm>
#include "Statistics.h"
#include "../Menu.h"

/**
 * @brief Constructor of Statistics a class that extends MenuItem
 * @param currMenuPage the current page of the menu
 * @param database database that stores all the information
 */
Statistics::Statistics(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

bool comparePair(pair<string, int> a1, pair<string, int> a2){
    return a1.second > a2.second;
}

/**
 * @brief Calculates the graph's diameter
 * @param airline Airline code
 * @param country Country name
 * @return diameter
 * Complexity: O(V * (V + E)) being V the number of vertices in the graph and E de number of edges
 */
int Statistics::diameter(string airline, string country){
    int max = 0;

    Graph flights = database->getFlightsGraph();
    for(auto airport : database->getFlightsGraph().getNodes()){
        string airportCode = airport.first;
        int diameter = flights.diameterBfs(airportCode, airline, country,database->getAirports());
        if(diameter > max) max = diameter;
    }
    return max;
}

string space(int s){
    string ans;
    for(int i = 0; i < s; i++){
        ans.push_back(' ');
    }
    return ans;
}

/**
 * @brief Displays the statistics
 * @param nAirports Amount of airports
 * @param nFlights Amount of flights
 * @param nAirlines Amount of airlines
 * @param diameter Graph's diameter
 * Complexity: O(1)
 */
void drawStatistics(int nAirports, int nFlights, int nAirlines, int diameter ){
    system("clear");
    cout << "\033[0m";
    cout << " ______________________________________________________________________________" << endl;
    cout << "|\033[40m                                    Statistics                                \033[0m|" << endl;
    cout << "|\033[40m------------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m Airports     | Flights      | Airlines     | Diameter     |                  \033[0m|" << endl;
    cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[100m " << nAirports << space(13-to_string(nAirports).length())<<"| "<< nFlights << space(13-to_string(nFlights).length()) <<"| "<< nAirlines << space(13-to_string(nAirlines).length()) <<"| "<< diameter <<space(13-to_string(diameter).length()) <<"|                  \033[0m|" << endl;
    cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m                                                                              \033[0m|" << endl;
    cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
    string  a;
    cout<<"\033[32mEnter anything to go back: ";
    cin >>a;

}

/**
 * @brief Displays the top airports
 * @param airports top airports
 * Complexity: O(1)
 */
void drawTopAirports(vector<Airport> airports){
    system("clear");
    cout << "\033[0m";
    cout << " ______________________________________________________________________________" << endl;
    cout << "|\033[40m                                  Top Airports                                \033[0m|" << endl;
    cout << "|\033[40m------------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m Code     | Name                                                              \033[0m|" << endl;
    cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
    int i = 0;
    for(Airport airport : airports){
        cout << "|";
        if(i%2 == 0){
            cout << "\033[47m"
                 << "\033[30m";
        }
        else{
            cout << "\033[100m";
        }
        cout << " " << airport.getCode() << space(9-airport.getCode().length()) << "| " << airport.getName() << space(66 - airport.getName().length()) << "\033[0m|" << endl;
        i++;
    }
    cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m                                                                              \033[0m|" << endl;
    cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
    string  a;
    cout<<"\033[32mEnter anything to go back: ";
    cin >>a;
}

/**
 * @brief Calculates the top airports with the most flights
 * @param airline Airline code
 * @param country Country name
 * @return Airports with most flights
 * Complexity: O(V*E + V*log(V)) being V the number of vertices in the graph and E de number of edges
 */
vector<Airport> Statistics::topAirportFlights(string airline, string country){
    int k = 10;
    vector<pair<string, int>> results;
    for(auto node : database->getFlightsGraph().getNodes()){
        bool hasAgency = false;
        Airport airport= database->getAirport(node.first);
        if(airport.getCountry() == country or country == "") {
            for (auto e: node.second.adj) {
                if (airline == e.airlineCode or airline == ""){
                    hasAgency = true;
                    break;
                }
            }
            if (hasAgency) {
                pair<string, int> r = {airport.getCode(), node.second.adj.size()};
                results.push_back(r);
            }
        }
    }
    std::sort(results.begin(), results.end(), comparePair);
    vector<Airport> result;
    if(k > results.size()) k = results.size();
    for(int i = 0; i < k; i++){
        result.push_back(database->getAirport(results[i].first));
    }
    return result;
}

/**
 * @brief Calculates the top airports with most airlines
 * @param airline Airline code
 * @param country Country name
 * @return Airports with most airlines
 * Complexity: O(V * E + V*log(V)) being V the number of vertices in the graph and E de number of edges
 */
vector<Airport> Statistics::topAirportAirlines(string airline, string country){
    int k = 10;
    vector<pair<string, int>> results;
    for(auto node : database->getFlightsGraph().getNodes()){
        Airport airport=database->getAirport(node.first);
        if(country == "" or airport.getCountry() == country){
            bool hasAgency = false;
            unordered_set<string> airlines;
            for (auto e: node.second.adj) {
                if (e.airlineCode == airline or airline == "") {
                    hasAgency = true;
                    airlines.insert(e.airlineCode);
                }
            }
            if (hasAgency) {
                pair<string, int> r = {airport.getCode(), airlines.size()};
                results.push_back(r);
            }
        }
    }
    std::sort(results.begin(), results.end(), comparePair);
    vector<Airport> result;
    if(k > results.size()) k = results.size();
    for(int i = 0; i < k; i++){
        result.push_back(database->getAirport(results[i].first));
    }
    return result;
}

/**
 * @brief Interacts with the user and makes the search for statistics of the global flights network or an airline or a country ,more user friendly
 * Complexity: O((V * E) + (V * E + V*log(V)) + (V * (V + E))) being V the number of vertices in the graph and E de number of edges
 */
void Statistics::execute() {
    bool c = true;
    Menu menu = Menu("../files/statisticsMainMenu");
    Menu statsMenu = Menu("../files/statisticsMenu");
    menu.draw();
    string option;
    string airline = "";
    string country = "";
    vector<Airport> airports;
    cout << "\033[32mInsert an option: ";
    while (c) {
        cin >> option;
        if (option.length() == 1 && isdigit(option[0])) {
            int nAirports = 0;
            int nFlights = 0;
            string country;
            switch (option[0]) {
                case '1': {
                    c = false;
                    for (auto node: database->getFlightsGraph().getNodes()) {
                        nFlights += node.second.adj.size();
                    }
                    statsMenu.draw();
                    bool flag = true;
                    cout << "\033[32m Insert an option: ";
                    while (flag) {
                        cin >> option;
                        string s;
                        if (option.length() == 1 && isdigit(option[0])) {
                            switch (option[0]) {
                                case '1': {
                                    flag = false;
                                    drawStatistics(database->getFlightsGraph().getNodes().size(), nFlights,
                                                   database->getAirlines().size(),
                                                   diameter(airline,country));
                                    break;
                                }
                                case '2': {
                                    flag = false;
                                    drawTopAirports(topAirportFlights(airline, country));
                                    break;
                                }

                                case '3': {
                                    flag = false;
                                    drawTopAirports(topAirportAirlines(airline, country));
                                    break;
                                }

                                default:
                                    cout << "\033[31mInsert a valid option: \033[32m";
                            }
                        }
                    }
                    break;
                }
                case '2': {
                    c = false;
                    cout << "\033[32mIntroduce the country: ";
                    cin >> country;
                    for (auto airport: database->getAirports()) {
                        if (airport.getCountry() == country) {
                            nAirports++;
                        }
                    }
                    if (nAirports > 0) {
                        unordered_set<string> airlines;
                        for (auto node: database->getFlightsGraph().getNodes()) {
                            if (database->getAirports().find(node.first)->getCountry() == country) {
                                nFlights += node.second.adj.size();
                                for (auto edge: node.second.adj) {
                                    airlines.insert(edge.airlineCode);
                                }
                            }
                        }
                        statsMenu.draw();
                        bool flag = true;
                        cout << "\033[32m Insert an option: ";
                        while (flag) {
                            cin >> option;
                            if (option.length() == 1 && isdigit(option[0])) {
                                switch (option[0]) {
                                    case '1':
                                        flag = false;
                                        drawStatistics(nAirports, nFlights, airlines.size(),
                                                       diameter(airline, country));

                                        break;

                                    case '2':
                                        flag = false;
                                        drawTopAirports(topAirportFlights(airline, country));

                                        break;

                                    case '3':
                                        flag = false;
                                        drawTopAirports(topAirportAirlines(airline, country));

                                        break;

                                    default:
                                        cout << "\033[31mInsert a valid option: \033[32m";
                                }
                            }
                        }

                    } else {
                        cout << "\033[31m"
                             << "Country not found!"
                             << "\033[0m" << endl;
                        cout << "\033[32mEnter anything to go back: ";
                        cin >> country;
                    }
                        break;
                    }
                    case '3': {
                        string airline;
                        c = false;
                        cout << "\033[32mIntroduce the airline code: ";
                        cin >> airline;
                        for (auto node: database->getFlightsGraph().getNodes()) {
                            bool hasAirline = false;
                            for (auto edge: node.second.adj) {
                                if (edge.airlineCode == airline) {
                                    hasAirline = true;
                                    nFlights++;
                                }
                            }
                            if (hasAirline) {
                                nAirports++;
                            }
                        }
                        if (nAirports > 0) {
                            statsMenu.draw();
                            bool flag = true;
                            cout << "\033[32m Insert an option: ";
                            while (flag) {
                                cin >> option;
                                if (option.length() == 1 && isdigit(option[0])) {
                                    switch (option[0]) {
                                        case '1':
                                            flag = false;
                                            drawStatistics(nAirports, nFlights, 1,
                                                           diameter(airline, country));

                                            break;

                                        case '2':
                                            flag = false;
                                            drawTopAirports(topAirportFlights(airline, country));

                                            break;

                                        case '3':
                                            flag = false;
                                            drawTopAirports(topAirportAirlines(airline, country));

                                            break;

                                        default:
                                            cout << "\033[31mInsert a valid option:\033[32m ";
                                    }
                                }
                            }
                        } else {
                            cout << "\033[31m"
                                 << "Airline not found!"
                                 << "\033[0m" << endl;
                            cout << "\033[32mEnter anything to go back: ";
                            cin >> airline;
                        }
                        break;
                    }
                    case '4':
                        c = false;
                    break;
                    default:
                        cout << "\033[31m"
                             << "Airline not found!"
                             << "\033[0m" << endl;
                }
            }
        }
    }