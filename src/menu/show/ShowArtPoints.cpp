#include "ShowArtPoints.h"

/**
 * @brief Constructor of ShowArtPoints a class that extends Show.
 * @param currMenuPage menu we are currently in
 * @param database program's database
 */
ShowArtPoints::ShowArtPoints(int &currMenuPage, Database &database) : Show(currMenuPage, database) {}

/**
 * @brief Helper function that runs all other methods to calculate, organize, and print the articulation points of the graph
 * @see AirportOrganizer::organize(vector<Airport> &airports) const
 * @see Graph::artPoints(const airportHTable &airports, const unordered_set<string> &airlines)
 * @see paginationController(vector<Name> data)
 */
void ShowArtPoints::execute() {
    AirportOrganizer airportOrganizer;
    vector<Airport> airports = database->getFlightsGraph().artPoints(database->getAirports(), chooseAirlines());
    airportOrganizer.organize(airports);
    paginationController(airports);
}

/**
 *
 * @brief Lets the user choose the airlines he wants to travel with. Not giving any input makes all the airlines the actual input
 * @return hash table with the desired airlines
 */
unordered_set<string> ShowArtPoints::chooseAirlines() {
    unordered_set<string> chosenAirlines;
    airlineHTable airlines = database->getAirlines();
    string input;

    cout << "Choose all airlines you accept to travel with. Press 'q' when you are done. If you accept travelling with every airline quit without adding any airline" << endl;
    while (true) {
        cin >> input;
        if (input == "q") {
            if (chosenAirlines.empty()) {
                for (auto airline: airlines)
                    chosenAirlines.insert(airline.getCode());
            }
            return chosenAirlines;
        }

        else if (airlines.find(Airline(input, "", "", "")) != airlines.end()) {
            cout << "Added " << input << " to chosen airlines" << endl;
            chosenAirlines.insert(input);
        }

        else
            cout << input << " isn't a valid airline. Please insert a valid airline: ";
    }
}