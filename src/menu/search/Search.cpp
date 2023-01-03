#include "Search.h"
#include "../Menu.h"

Search::Search(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

int getFloat(float &option) {
    cin >> option;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    return false;
}

unordered_set<string> airportInput(Database& database) {
    unordered_set<string> result;
    string input;
    cout << "Introduce the airport code: ";
    while (true) {
        cin >> input;
        if (database.getAirports().find(Airport(input, "", "", "", 0, 0)) == database.getAirports().end()) {
            cout << "Introduce a valid airport code: ";
        } else{
            result.insert(input);
            break;
        }
    }
    return result;
}

unordered_set<string> cityInput(Database& database) {
    unordered_set<string> result;
    string city;
    cout << "Introduce the city code: ";
    while (true) {
        cin >> city;

        for (char& c: city)
            c = tolower(c);

        for (Airport airport: database.getAirports()) {
            string airportCity = airport.getCity();

            for (char& c: airportCity)
                c = tolower(c);

            if (airportCity == city)
                result.insert(airport.getCode());
        }

        /* Acho q n funciona, o find usa a função booleana da hash que compra codigos
        if (database.getAirports().find(Airport("", "", city, "", 0, 0)) == database.getAirports().end()){
            cout << "Introduce a valid city code: "; */

        if (!result.empty())
            break;
        else
            cout << "Please insert a valid city: ";
    }
    return result;
}

unordered_set<string> locationInput(Database& database) {
    unordered_set<string> result;
    float latitude;
    float longitude;
    float maxDist;
    cout << "Introduce the latitude of the location [-90; 90]: ";
    while (true) {
        if (getFloat(latitude) || latitude < -90 || latitude > 90)
            cout << "Insert a valid float number: ";
        else
            break;
    }
    cout << "Introduce the longitude of the location [-180; 180]: ";
    while (true){
        if (getFloat(longitude) || longitude < -180 || longitude > 180)
            cout << "Insert a valid float number: ";
        else
            break;
    }

    cout << "Introduce the max distance the airport should be (in km): ";
    while (true){
        if (getFloat(maxDist) || maxDist < 0)
            cout << "Insert a valid float number: ";
        else
            break;
    }

    Coordinate location = Coordinate(latitude, longitude);

    for(Airport airport : database.getAirports()){
        if(location.distance(airport.getCoordinate()) <= maxDist){
            result.insert(airport.getCode());
        }
    }
    return result;
}

void Search::execute() {
    unordered_set<string> originAirports, destAirports, airlines;

    vector<string> buttons = readMenuButtons();
    drawMenu(buttons);
    originAirports = chooseAirports();
    drawMenu(buttons);
    destAirports = chooseAirports();
    airlines = chooseAirlines();
    trips minimalFlights = getMinimalFlights(originAirports, destAirports, airlines);
    printMinimalFlights(minimalFlights);
    cout<<"Enter anything to go back: ";
    string wait;
    cin>>wait;
}

vector<string> Search::readMenuButtons() {
    ifstream file("../files/localMenu");
    vector<string> buttons;

    for(string button; getline(file,button);){
        buttons.push_back(button);
    }

    return buttons;
}

void Search::drawMenu(vector<string> buttons) {
    system("clear");
    string display;
    display =" _____________________________________________ \n"
             "|<<<<<<<<<<<<<<<<<>  Menu  <>>>>>>>>>>>>>>>>>>|\n"
             "|---------------------------------------------|\n";


    for(int i=0; i<buttons.size();i++){
        display+="| ["+to_string(i+1)+"] "+ buttons[i];
        for(int j=0; j<(39 - buttons[i].length());j++)
            display+=" "; //adding spaces to format the menu
        if(i<9) display+=' ';
        display+="|\n";
    }
    display+="|_____________________________________________|\n";
    cout<<display<<endl;
}

unordered_set<string> Search::chooseAirports() {
    bool c = true;
    string option;
    unordered_set<string> input;
    while (c) {
        cin >> option;
        if (option.length() == 1 && isdigit(option[0])) {
            switch (option[0]) {
                case '1':
                    input = airportInput(database);
                    c = false;
                    break;
                case '2':
                    input = cityInput(database);
                    c = false;
                    break;
                case '3':
                    input = locationInput(database);
                    c = false;
                    break;
                case '4':
                    currMenuPage = 0;
                    c = false;
                    break;
                default:
                    break;
            }
        }
        if(c) cout << "Choose a valid option: ";
    }
    return input;
}

unordered_set<string> Search::chooseAirlines() {
    unordered_set<string> chosenAirlines;
    airlineHTable airlines = database.getAirlines();
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

trips Search::getMinimalFlights(unordered_set<string> originAirports, unordered_set<string> destAirports, unordered_set<string> airlines) {
    Graph flights = database.getFlightsGraph();
    trips minimalTrips;
    trips currTrips;

    for (string originAirport: originAirports) {
        currTrips = flights.minFlightsBFS(originAirport, destAirports, airlines);

        if (currTrips.empty())
            continue;

        // Calculated flights are minimal as well
        if (minimalTrips.empty() || minimalTrips[0].size() == currTrips[0].size()) {
            minimalTrips.insert(minimalTrips.end(), currTrips.begin(), currTrips.end());
        }

        // Calculated flights are less than the ones calculated previously
        else if (minimalTrips[0].size() > currTrips[0].size()) {
            minimalTrips = currTrips;
        }

        // Else calculated flights are more than the ones calculated previously and get ignored
    }

    return minimalTrips;
}

void Search::printMinimalFlights(trips minimalFlights) {
    for (auto trip: minimalFlights) {
        cout << "A trip:" << endl;
        for (auto airport = trip.begin(); airport != --trip.end(); airport++) {
            cout << '\t' << airport->first << " --- " + (++airport)->second + " ---> " << airport->first << endl;
            airport--;
        }
        cout << endl;
    }

}