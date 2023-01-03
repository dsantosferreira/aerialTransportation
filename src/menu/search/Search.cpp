#include "Search.h"
#include "../Menu.h"

Search::Search(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

unordered_set<string> airportInput(Database& database) {
    unordered_set<string> result;
    string input;
    cout << "Introduce the airport code: ";
    while (true) {
        cin >> input;
        if (database.getAirports().find(Airport("input", "", "", "", 0, 0)) == database.getAirports().end()) {
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
        if (database.getAirports().find(Airport("", "", city, "", 0, 0)) == database.getAirports().end()){
            cout << "Introduce a valid city code: ";
        } else{
            break;
        }
    }
    for(Airport airport : database.getAirports()){
        if(airport.getCity() == city){
            result.insert(airport.getCode());
        }
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
        cin >> latitude;
        break;
    }
    cout << "Introduce the longitude of the location: ";
    while (true){
        cin >> longitude;
        break;
    }

    cout << "Introduce the max distance the airport should be (in km): ";
    while (true){
        cin >> maxDist;
        break;
    }

    Coordinate location = Coordinate(latitude, longitude);

    for(Airport airport : database.getAirports()){
        if(location.distance(airport.getCoordinate()) < maxDist){
            result.insert(airport.getCode());
        }
    }
    return result;
}

void Search::execute() {
    ifstream file("../files/localMenu");
    vector<string> buttons;
    for(string button; getline(file,button);){
        buttons.push_back(button);
    }
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
            }
        }
        if(c) cout << "Choose a valid option: ";
    }
}

