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
    cout << "Introduce the latitude of the location: ";
    while (true) {
        if (getFloat(latitude))
            cout << "Insert a valid float number: ";
        else
            break;
    }
    cout << "Introduce the longitude of the location: ";
    while (true){
        if (getFloat(longitude))
            cout << "Insert a valid float number: ";
        else
            break;
    }

    cout << "Introduce the max distance the airport should be (in km): ";
    while (true){
        if (getFloat(maxDist))
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

}

vector<string> Search::readMenuButtons() {
    ifstream file("../files/localMenu");
    vector<string> buttons;

    for(string button; getline(file,button);){
        buttons.push_back(button);
    }
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
}

unordered_set<string> Search::chooseAirlines() {
    unordered_set<string> chosenAirlines;
    airlineHTable airlines = database.getAirlines();
    string input;

    cout << "Choose all airlines you accept to travel with. Press 'q' when you are done.";
    while (true) {
        if (input == "q")
            return chosenAirlines;
        else if (airlines.find(Airline(input, "", "", "")) != airlines.end()) {
            cout << "Added " << input << " to chosen airlines" << endl;
            chosenAirlines.insert(input);
        }
        else
            cout << input << " isn't a valid airline. Please insert a valid airline: ";
    }
}