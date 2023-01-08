#include <algorithm>
#include "Statistics.h"
#include "../Menu.h"

Statistics::Statistics(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

bool comparePair(pair<string, int> a1, pair<string, int> a2){
    return a1.second > a2.second;
}

int Statistics::diameter(unordered_set<string> airlines, unordered_set<string> countries){
    int max = 0;
    airportHTable airports = database->getAirports();
    Graph flights = database->getFlightsGraph();
    for(auto airport : airports){
        string airportCode = airport.getCode();
        int diameter = flights.bfs(airportCode, airlines, countries, airports);
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

vector<Airport> Statistics::topAirportFlights(unordered_set<string> airlines, unordered_set<string> countries){
    int k = 10;
    auto airports = database->getAirports();
    vector<pair<string, int>> results;
    for(auto airport : airports){
        bool hasAgency = false;
        if(countries.find(airport.getCountry()) != countries.end()) {
            Graph::Node airportNode = database->getFlightsGraph().getNodes().find(airport.getCode())->second;
            for (auto e: airportNode.adj) {
                if (airlines.find(e.airlineCode) != airlines.end()){
                    hasAgency = true;
                    break;
                }
            }
            if (hasAgency) {
                pair<string, int> r = {airport.getCode(), airportNode.adj.size()};
                results.push_back(r);
            }
        }
    }
    std::sort(results.begin(), results.end(), comparePair);
    vector<Airport> result;
    for(int i = 0; i < k; i++){
        result.push_back(database->getAirport(results[i].first));
    }
    return result;
}

vector<Airport> Statistics::topAirportAirlines(unordered_set<string> airlines, unordered_set<string> countries){
    int k = 10;
    auto airports = database->getAirports();
    vector<pair<string, int>> results;
    for(auto airport : airports){
        if(countries.find(airport.getCountry()) != countries.end()) {
            bool hasAgency = false;
            unordered_set<string> agencies;
            Graph::Node airportNode = database->getFlightsGraph().getNodes().find(airport.getCode())->second;
            for (auto e: airportNode.adj) {
                if (airlines.find(e.airlineCode) != airlines.end()) {
                    hasAgency = true;
                    agencies.insert(e.airlineCode);
                }
            }
            if (hasAgency) {
                pair<string, int> r = {airport.getCode(), agencies.size()};
                results.push_back(r);
            }
        }
    }
    std::sort(results.begin(), results.end(), comparePair);
    vector<Airport> result;
    for(int i = 0; i < k; i++){
        result.push_back(database->getAirport(results[i].first));
    }
    return result;
}

void Statistics::execute() {
    bool c = true;
    Menu menu = Menu("../files/statisticsMainMenu");
    Menu statsMenu = Menu("../files/statisticsMenu");
    menu.draw();
    string option;
    unordered_set<string> airlines;
    unordered_set<string> countries;
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
                    for(Airline airline: database->getAirlines()) airlines.insert(airline.getCode());
                    for (auto node: database->getFlightsGraph().getNodes()) {
                        nFlights += node.second.adj.size();
                        auto a = database->getAirports().find(node.first);
                        countries.insert(a->getCountry());
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
                                                   12);
                                    cout << "\033[32mEnter anything to go back: ";
                                    cin >> s;
                                    cout<<"\033[0m";
                                    break;
                                }
                                case '2': {
                                    flag = false;
                                    drawTopAirports(topAirportFlights(airlines, countries));
                                    string s;
                                    break;
                                }

                                case '3': {
                                    flag = false;
                                    drawTopAirports(topAirportAirlines(airlines, countries));
                                    string s;
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
                            countries.insert(country);
                            nAirports++;
                        }
                    }
                    if (!countries.empty()) {
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
                                                       diameter(airlines, countries));
                                        cout << "\033[32mEnter anything to go back: ";
                                        cin >> country;

                                        break;

                                    case '2':
                                        flag = false;
                                        drawTopAirports(topAirportFlights(airlines, countries));
                                        cout << "\033[32mEnter anything to go back: ";
                                        cin >> country;
                                        break;

                                    case '3':
                                        flag = false;
                                        drawTopAirports(topAirportAirlines(airlines, countries));
                                        cout << "\033[32mEnter anything to go back: ";
                                        cin >> country;
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
                                    airlines.insert(airline);
                                    hasAirline = true;
                                    nFlights++;
                                }
                            }
                            if (hasAirline) {
                                countries.insert(database->getAirports().find(node.first)->getCountry());
                                nAirports++;
                            }
                        }
                        if (!airlines.empty()) {
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
                                                           diameter(airlines, countries));
                                            cout << "\033[32mEnter anything to go back: ";
                                            cin >> airline;
                                            break;

                                        case '2':
                                            flag = false;
                                            drawTopAirports(topAirportFlights(airlines, countries));
                                            cout << "\033[32mEnter anything to go back: ";
                                            cin >> airline;
                                            break;

                                        case '3':
                                            flag = false;
                                            drawTopAirports(topAirportAirlines(airlines, countries));
                                            cout << "\033[32mEnter anything to go back: ";
                                            cin >> airline;
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