#include "Database.h"

Database::Database() {
    readAirports();
    readAirlines();
    createFlightsGraph();
}

void Database::readAirports() {
    ifstream in("../files/airports.csv");
    string code, name, city, country, aLine, latitude, longitude;
    getline(in, aLine);
    while (getline(in, aLine)) {
        istringstream inn(aLine);
        getline(inn, code, ',');
        getline(inn, name, ',');
        getline(inn, city, ',');
        getline(inn, country, ',');
        getline(inn, latitude, ',');
        getline(inn, longitude, ',');
        airports.insert(Airport(code, name, city, country, stof(latitude), stof(longitude)));
    }
}

void Database::readAirlines() {
    ifstream in("../files/airlines.csv");
    string code, name, callSign, country, aLine;
    getline(in, aLine);
    while (getline(in, aLine)) {
        istringstream inn(aLine);
        getline(inn, code, ',');
        getline(inn, name, ',');
        getline(inn, callSign, ',');
        getline(inn, country, ',');
        airlines.insert(Airline(code, name, callSign, country));
    }
}

void Database::createFlightsGraph() {
    flights = Graph(airports.size(), airports, true);

    ifstream in("../files/flights.csv");
    string source, target, airline, aLine;
    getline(in, aLine);
    while (getline(in, aLine)) {
        istringstream inn(aLine);
        getline(inn, source, ',');
        getline(inn, target, ',');
        getline(inn, airline, ',');
        flights.addEdge(source, target, airline);
    }
}
airportHTable Database::getAirports() const {
    return airports;
}
airlineHTable Database::getAirlines() const {
    return airlines;
}
Graph Database::getGraph() const {
    return this->flights;
}