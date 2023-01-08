#include "ShowArtPoints.h"

ShowArtPoints::ShowArtPoints(int &currMenuPage, Database &database) : Show(currMenuPage, database) {}

void ShowArtPoints::execute() {
    AirportOrganizer airportOrganizer;
    vector<Airport> airports = database->getFlightsGraph().artPoints(database->getAirports(), chooseAirlines());
    airportOrganizer.organize(airports);
    paginationController(airports);
}

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