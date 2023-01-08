#include "Database.h"

/**Constructor of Database, it will read several files and store its information, such as the airports, airlines and the flights
 * @brief Constructor of Database
 * @see Database::readAirports()
 * @see Database::readAirlines()
 * @see Database::createFlightsGraph()
 */
Database::Database()
{
    readAirports();
    readAirlines();
    createFlightsGraph();
}

/**
 * @brief Reads the airports from the file and stores its data on an unordered_set
 * complexity O(N) being N the number of airports on the file
 */
void Database::readAirports()
{
    ifstream in("../files/airports.csv");
    string code, name, city, country, aLine, latitude, longitude;
    getline(in, aLine);
    while (getline(in, aLine))
    {
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

/**
 * @brief Reads the airlines from a file and stores its data on an unordered_set
 * complexity O(N) being N the number of airlines on the file
 */
void Database::readAirlines()
{
    ifstream in("../files/airlines.csv");
    string code, name, callSign, country, aLine;
    getline(in, aLine);
    while (getline(in, aLine))
    {
        istringstream inn(aLine);
        getline(inn, code, ',');
        getline(inn, name, ',');
        getline(inn, callSign, ',');
        getline(inn, country, ',');
        airlines.insert(Airline(code, name, callSign, country));
    }
}

/**
 * @brief Reads the flights from a file and stores its data on a graph
 * @see Graph::addEdge(string src, string dest, string airline, float weight = 0)
 * complexity O(N) being N the number of flights on the file
 */
void Database::createFlightsGraph()
{
    flights = Graph(airports.size(), airports, true);
    undirectedFlights = Graph(airports.size(), airports, false);

    ifstream in("../files/flights.csv");
    string source, target, airline, aLine;
    getline(in, aLine);
    while (getline(in, aLine))
    {
        istringstream inn(aLine);
        getline(inn, source, ',');
        getline(inn, target, ',');
        getline(inn, airline, ',');
        Coordinate c1 = airports.find(Airport(source, "", "", "", 0, 0))->getCoordinate();
        Coordinate c2 = airports.find(Airport(target, "", "", "", 0, 0))->getCoordinate();
        flights.addEdge(source, target, airline, c1.distance(c2));
        undirectedFlights.addEdge(source, target, airline, c1.distance(c2));
    }
}

/**
 * @return the graph with the flights
 */
Graph Database::getFlightsGraph() const
{
    return flights;
}

Graph Database::getUndirectedFlightsGraph() const {
    return undirectedFlights;
}

/**
 * @return the unordered_set with the airports
 */
airportHTable Database::getAirports() const
{
    return airports;
}

/**
 * @return the unordered_set with the airlines
 */
airlineHTable Database::getAirlines() const
{
    return airlines;
}

/**
 * @brief Returns the airline corresponding to the airline code provided as input
 * @param code airline code from the airline we want to return
 * @return the airline corresponding to the airline code given
 * complexity O(1)
 */
Airline Database::getAirline(string code) const
{
    return *airlines.find(Airline(code, "", "", ""));
}

/**
 * @brief Returns the airport corresponding to the airport code provided as input
 * @param code airport code from the airport we want to return
 * @return the airport corresponding to the airport code given
 * complexity O(1)
 */
Airport Database::getAirport(string code) const
{
    return *airports.find(Airport(code));
}