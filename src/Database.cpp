#include "Database.h"
/**Constructor of Database, it will read several files and store its information, such as the Airports, Airlines and the flights
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
 * @brief reads the airports from the file and stores its data on an unordered_set
 * complexity O(N) being N the number of Airports
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
 * @brief reads the airlines from a file and stores its data on an unordered_set
 * complexity O(N) being N the number of Airlines
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
 * @brief reads the flights from a file and stores its data on a graph
 * complexity O(N) being N the number of flights
 */
void Database::createFlightsGraph()
{
    flights = Graph(airports.size(), airports, true);

    ifstream in("../files/flights.csv");
    string source, target, airline, aLine;
    getline(in, aLine);
    while (getline(in, aLine))
    {
        istringstream inn(aLine);
        getline(inn, source, ',');
        getline(inn, target, ',');
        getline(inn, airline, ',');
        flights.addEdge(source, target, airline);
    }
}
/**
 *
 * @return the graph with the flights
 */
Graph Database::getFlightsGraph() const
{
    return flights;
}
/**
 *
 * @return the unordered_set with the Airports
 */
airportHTable Database::getAirports() const
{
    return airports;
}
/**
 *
 * @return the unordered_set with the Airlines
 */
airlineHTable Database::getAirlines() const
{
    return airlines;
}
/**
 * @brief returns the Airline corresponding to the airline code given
 * @param code airline code from the airline we want to return
 * @return the airline corresponding to the airline code given
 * complexity O(1)
 */
Airline Database::getAirline(string code) const
{
    return *airlines.find(Airline(code, "", "", ""));
}
/**
 * @brief returns the Airport corresponding to the airport code given
 * @param code airport code from the airport we want to return
 * @return the airport corresponding to the airport code given
 * complexity O(1)
 */
Airport Database::getAirport(string code) const
{
    return *airports.find(Airport(code));
}