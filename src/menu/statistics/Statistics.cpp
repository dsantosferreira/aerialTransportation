#include <algorithm>
#include "Statistics.h"

Statistics::Statistics(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

bool comparePair(pair<string, int> a1, pair<string, int> a2){
    return a1.second > a2.second;
}

int diameter(Database& database, unordered_set<string> airlines, unordered_set<string> countries){
    int max = 0;
    airportHTable airports = database.getAirports();
    Graph flights = database.getFlightsGraph();
    for(auto airport : airports){
        string airportCode = airport.getCode();
        flights.bfs(airportCode, airlines, countries, airports);
        for(auto node : flights.getNodes()){
            if(node.second.distance > max){
                max = node.second.distance;
            }
        }
    }
    return max;
}

vector<Airport> topAirportFlights(Database& database, unordered_set<string> airlines, unordered_set<string> countries){
    int k = 0;
    bool c = true;
    string input;
    while (c){
        bool flag = true;
        cin >> input;
        for(char s : input){
            if(!isdigit(s)) flag = false;
        }
        if(flag) k = stoi(input);
        if(k > 0) c = false;
    }
    auto airports = database.getAirports();
    vector<pair<string, int>> results;
    for(auto airport : airports){
        bool hasAgency = false;
        if(countries.find(airport.getCountry()) != countries.end()) {
            Graph::Node airportNode = database.getFlightsGraph().getNodes().find(airport.getCode())->second;
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
        result.push_back(database.getAirport(results[i].first));
    }
    return result;
}

vector<Airport> topAirportAirlines(Database& database, unordered_set<string> airlines, unordered_set<string> countries){
    int k = 0;
    bool c = true;
    string input;
    while (c){
        bool flag = true;
        cin >> input;
        for(char s : input){
            if(!isdigit(s)) flag = false;
        }
        if(flag) k = stoi(input);
        if(k > 0) c = false;
    }
    auto airports = database.getAirports();
    vector<pair<string, int>> results;
    for(auto airport : airports){
        if(countries.find(airport.getCountry()) != countries.end()) {
            bool hasAgency = false;
            unordered_set<string> agencies;
            Graph::Node airportNode = database.getFlightsGraph().getNodes().find(airport.getCode())->second;
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
        result.push_back(database.getAirport(results[i].first));
    }
    return result;
}

void topAirport(Database& database, unordered_set<string> agencies, unordered_set<string> countries){
    bool c = true;
    vector<Airport> result;
    string option;
    while(c){
        cin >> option;
        if(option.length() == 1 && isdigit(option[0])){
            switch (option[0]) {
                case '1':
                    result = topAirportFlights(database, agencies, countries);
                    c = false;
                    break;
                case '2':
                    result = topAirportAirlines(database, agencies, countries);
                    c = false;
                    break;

            }
        }
    }

}


void Statistics::execute() {
    bool c = true;
    string option;
    unordered_set<string> airlines;
    unordered_set<string> countries;
    cout << "INSERT OPTION: ";
    while (c) {
        cin >> option;
        if (option.length() == 1 && isdigit(option[0])) {
            int nAirlines = 0;
            int nAirports = 0;
            int nFlights = 0;
            bool flag = true;
            string country;
            switch (option[0]){
                case '1':
                    c = false;
                    for(auto node : database.getFlightsGraph().getNodes()){
                        for(auto e : node.second.adj){
                            airlines.insert(e.airlineCode);
                        }
                        nFlights += node.second.adj.size();
                        auto a = database.getAirports().find(node.first);
                        countries.insert(a->getCountry());
                    }
                    cout << "Nº DE AEROPORTOS: " << database.getFlightsGraph().getNodes().size() << endl;
                    cout << "Nº DE VOOS: " << nFlights << endl;
                    cout << "Nº DE COMPANHIAS: " << database.getAirlines().size() << endl;
                    cout << "DIAMETRO: " << diameter(database, airlines, countries) << endl;
                    break;
                case '2':
                    c = false;
                    while (flag) {
                        cin >> country;
                        for (auto airport: database.getAirports()) {
                            if (airport.getCountry() == country) {
                                countries.insert(country);
                                nAirports++;
                            }
                        }
                        if (!countries.empty()) {
                            flag = false;
                            for (auto node: database.getFlightsGraph().getNodes()) {
                                if (database.getAirports().find(node.first) != database.getAirports().end() and database.getAirports().find(node.first)->getCountry() == country) {
                                    nFlights += node.second.adj.size();
                                }
                            }
                        } else {
                            cout << "Country not found: ";
                        }
                    }
                    cout << "Nº DE AEROPORTOS: " << nAirports << endl;
                    cout << "Nº DE VOOS: " << nFlights << endl;
                    cout << "Nº DE COMPANHIAS: " << nAirlines << endl;
                    cout << "DIAMETRO: " << diameter(database, airlines, countries) << endl;

                    break;
                case '3':
                    c = false;
                    string airline;
                    while (flag){
                        cin >> airline;
                        for(auto node : database.getFlightsGraph().getNodes()){
                            bool hasAirline = false;
                            for(auto edge : node.second.adj){
                                if(edge.airlineCode == airline){
                                    airlines.insert(airline);
                                    hasAirline = true;
                                }
                            }
                            if(hasAirline) nAirports++;
                        }
                        if(!airlines.empty()){
                            flag = false;
                        } else{
                            cout << "Airline not found: ";
                        }
                    }

                    cout << "Nº DE AEROPORTOS: " << nAirports << endl;
                    cout << "Nº DE VOOS: " << nFlights << endl;
                    cout << "DIAMETRO: " << diameter(database, airlines, countries) << endl;
                    break;
            }
        }
    }
}


