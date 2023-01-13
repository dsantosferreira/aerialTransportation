#include "Search.h"
#include "../Menu.h"

/**
 * @brief Constructor of DirectFlights a class that extends MenuItem
 * @param currMenuPage
 * @param database
 */
Search::Search(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

/**
 * @brief Tries to read a float value from user's input
 * @param option
 * @return true if input provided wasn't in the right format, false otherwise
 */
bool getFloat(float &option) {
    cin >> option;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    return false;
}

/**
 * @brief Asks the user for the maximum of airlines he wants to travel with
 * @param maxAirlines maximum number of airlines to travel with
 * @return boolean: true if incorrect input was provided, false otherwise
 */
bool Search::getMaximumAirlines(int &maxAirlines) {
    string option;
    cin >> option;
    if (option == "q" || option == "Q") {
        maxAirlines = INT32_MAX;
        return false;
    }
    else {
        try{
            maxAirlines = stoi(option);
            if (maxAirlines <= 0) {
                cout << "Insert a value higher than 0: ";
                return true;
            }
        } catch (invalid_argument){
            cout << "Insert an integer: ";
            return true;
        }
    }
    return false;
}

/**
 * @brief Asks the user for the desired airport code, returning the respective airport
 * @param database program's database
 * @return hash table with the desired airport
 */
unordered_set<string> Search::airportInput(Database& database) {
    unordered_set<string> result;
    string input;
    cout << "\033[32mIntroduce the airport code: ";
    while (true) {
        cin >> input;

        for (char &c : input) {
            c = toupper(c);
        }

        if (database.getAirports().find(Airport(input, "", "", "", 0, 0)) == database.getAirports().end()) {
            cout << "\033[31mIntroduce a valid airport code:\033[32m ";
        } else{
            result.insert(input);
            break;
        }
    }
    cout<<"\033[0m";
    return result;
}

/**
 * @brief Asks the user for the desired city, returning the airports in that city
 * @param database program's database
 * @return hash table with the airports from the desired city
 */
unordered_set<string> Search::cityInput(Database& database) {
    unordered_set<string> result;
    string city;
    cout << "\033[32mIntroduce the city code: ";
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

        if (!result.empty())
            break;
        else
            cout << "\033[31mPlease insert a valid city:\033[32m ";
    }
    cout<<"\033[0m";
    return result;
}

/**
 * Asks the user for the desired location's latitude, longitude and radius, forming a circle with the location as its center.
 * Returns all the airports in the formed circle
 * @brief Asks the user for the desired a location's latitude and longitude and radius, returning the airports in that area
 * @param database program's database
 * @see Coordinate::distance(Coordinate coordinate2) const
 * @return hash table with the airports from the desired area
 */
unordered_set<string> Search::locationInput(Database& database) {
    unordered_set<string> result;
    float latitude;
    float longitude;
    float maxDist;
    cout << "\033[32mIntroduce the latitude of the location [-90; 90]: ";
    while (true) {
        if (getFloat(latitude) || latitude < -90 || latitude > 90)
            cout << "\033[31mInsert a valid float number:\033[32m ";
        else
            break;
    }
    cout << "Introduce the longitude of the location [-180; 180]: ";
    while (true){
        if (getFloat(longitude) || longitude < -180 || longitude > 180)
            cout << "\033[31mInsert a valid float number:\033[32m ";
        else
            break;
    }

    cout << "Introduce the max distance the airport should be (in km): ";
    while (true){
        if (getFloat(maxDist) || maxDist < 0)
            cout << "\033[31mInsert a valid float number:\033[32m ";
        else
            break;
    }
    cout<<"\003";
    Coordinate location = Coordinate(latitude, longitude);

    for(Airport airport : database.getAirports()){
        if(location.distance(airport.getCoordinate()) <= maxDist){
            result.insert(airport.getCode());
        }
    }
    return result;
}

/**
 * @brief Compares two trips distance travelled
 * @param t1 first trip
 * @param t2 second trip
 * @return true if first trip's distance travelled is higher than second trip's distance travelled
 */
bool orderTrips(const trip &t1, const trip &t2) {
    return t1.second < t2.second;
}

/**
 * @brief Helper function that calls all the other methods that ask for input, calculate the minimal flights and print them
 * @see Menu::draw()
 * @see Search::chooseAirports()
 * @see Search::chooseAirlines()
 * @see Search::(selectMaximumAirlines()
 * @see Search::paginationController(trips minimalFlights) const;
 * @see orderTrips(const trip &t1, const trip &t2)
 * @see Graph::minFlightsBFS(unordered_set<string> origin, unordered_set<string> destinations, unordered_set<string> airlines, const int maxAirlines)
 */
void Search::execute() {
    pair<unordered_set<string>, bool> originAirports, destAirports;
    Graph g = database->getFlightsGraph();
    unordered_set<string> airlines;
    int maxAirlines;

    Menu menu("../files/localMenu");
    menu.draw();
    originAirports = chooseAirports();
    if (!originAirports.second)
        return;
    menu.draw();
    destAirports = chooseAirports();
    if (!destAirports.second)
        return;
    airlines = chooseAirlines();
    maxAirlines = selectMaximumAirlines();

    trips minimalFlights = g.minFlightsBFS(originAirports.first, destAirports.first, airlines, maxAirlines);

    sort(minimalFlights.begin(), minimalFlights.end(), orderTrips);

    if (minimalFlights.size() != 0)
        paginationController(minimalFlights);
    else {
        cout << "There are no flights available" << endl << endl;
        cout<<"\033[32mEnter anything to go back: ";
        string wait;
        cin>>wait;
        cout<<"\033[0m";
    }
}

/**
 * @brief Lets the user choose the airports he wants as input (a specific airport, a city, or a location)
 * @return pair of all the airports chosen and a boolean that checks if the user wanted to return to the main menu
 */
pair<unordered_set<string>, bool> Search::chooseAirports() {
    bool c = true;
    string option;
    pair<unordered_set<string>, bool> input;
    cout << "\033[32mChoose an option: ";
    while (c) {
        cin >> option;
        if (option.length() == 1 && isdigit(option[0])) {
            switch (option[0]) {
                case '1':
                    input = {airportInput(*database), true};
                    c = false;
                    break;
                case '2':
                    input = {cityInput(*database), true};
                    c = false;
                    break;
                case '3':
                    input = {locationInput(*database), true};
                    c = false;
                    break;
                case '4':
                    *currMenuPage = 0;
                    c = false;
                    input.second = false;
                    break;
                default:
                    break;
            }
        }
        if(c) cout << "\033[32mChoose a valid option: ";
    }
    cout<<"\033[0m";
    return input;

}

/**
 * @brief Lets the user choose the airlines he wants to use. Not giving any input makes all the airlines the actual input
 * @return pair of all the airports chosen and a boolean that checks if the user wanted to return to the main menu
 */
unordered_set<string> Search::chooseAirlines() {
    system("clear");
    unordered_set<string> chosenAirlines;
    airlineHTable airlines = database->getAirlines();
    string input;

    cout << "\033[32mChoose all airlines you accept to travel with. Press 'q' when you are done. If you accept travelling with every airline quit without adding any airline" << endl;
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
            cout <<"\033[31m"<< input << " isn't a valid airline. Please insert a valid airline:\033[32m ";
    }
}

/**
 * @brief Lets the user choose the maximum of different airlines he wants to travel with
 * @return number of maximum different airlines as an integer value
 */
int Search::selectMaximumAirlines() {
    int maxAirlines;

    system("clear");
    cout<<"\033[32m";
    cout << "Choose the maximum number of airlines you want to travel with. Write 'q' if you don't want an upper bound of airlines you travel with: ";
    while (getMaximumAirlines(maxAirlines));
    return maxAirlines;
}

/**
 * Controls the pagination of the drawn table. It allows the user to quit the menu, or jump to the next, previous or any other page directly.
 * @brief Controls the pagination of the drawn table.
 * @see Search::draw(int page, trip minimalTrip, int nPages) const
 * @param minimalFlights vector of minimal trips
 * Complexity: O(1)
 */
void Search::paginationController(trips minimalFlights) const {
    int page = 0;
    while (page >= 0 and page < minimalFlights.size())
    {
        string option;
        draw(page, minimalFlights[page], minimalFlights.size());
        bool cond = true;
        while (cond)
        {
            cout << endl
                 << "\033[32mChoose an option[n/p/q] or the number of the page you would want to go[1-" << minimalFlights.size() << "]: ";
            cond = true;
            cin >> option;

            if (option.length() == 1)
            {
                option= ::toupper(option[0]);
                switch (option[0])
                {
                    case 'N':
                        page++;
                        cond=false;
                        break;
                    case 'P':
                        page--;
                        cond=false;
                        break;
                    case 'Q':
                        page = -1;
                        cond=false;
                        break;
                    default:
                        cond = true;
                }
            }
            if(cond){
                int test;
                try{
                    cond=false;
                    test= stoi(option);
                }catch (invalid_argument){
                    cond=true;
                }
                if(!cond){
                    cond=true;
                    if(to_string(test).length()==option.length()){
                        if(test>0 and test <= minimalFlights.size()) {
                            page=test-1;
                            cond= false;
                        }
                    }

                }
            }
            if (cond)
                cout << "\033[31mInvalid input! Please enter a valid input: \033[0m";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

/**
 * Draws a table that displays the minimal flights. It makes use of a system of pagination that displays one trip per page
 * @brief Draws a table that displays the minimal flights from X origin airports to Y destination airports
 * @param page number of the drawn page
 * @param minimalTrip trip to print
 * @param nPages number of total pages
 * Complexity: O(1)
 */
void Search::draw(int page, trip minimalTrip, int nPages) const {
    int idx = 0;
    system("clear");
    cout<<"\033[0m";
    cout << " _____________________________________________________________________________" << endl;
    cout << "|\033[40m                               Minimal flights                               \033[0m|" << endl;
    cout << "|\033[40m-----------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m                                  Page(" << page + 1<<"/"<<nPages<<")";
    for (int i = 0; i <= 8 - to_string(page + 1).length()- to_string(nPages).length(); i++)
        cout << ' ';

    cout << "                           \033[0m|" << endl;
    cout << "|\033[40m-----------------------------------------------------------------------------\033[0m|" << endl;
    cout << "|\033[40m         Origin          |       Destination       |         Airline         \033[0m|" << endl;
    cout << "|\033[40m_____________________________________________________________________________\033[0m|" << endl;

    for (auto itr = minimalTrip.first.begin(); itr != --minimalTrip.first.end(); itr++) {
        cout << "|";
        if (idx % 2 == 0)
            cout << "\033[47m"
                 << "\033[30m";
        else
            cout << "\033[100m";
        idx = idx % 2 == 0 ? 1 : 0;

        /*
         * cout << '\t' << airport->first << " --- " + (++airport)->second + " ---> " << airport->first << endl;
         * airport--;
         */

        cout << "           " << itr->first << "           |";
        cout << "           " << (++itr)->first << "           |";
        cout << "           " <<  itr->second << "           ";
        itr--;


        cout << "\033[0m"
             << "|" << endl;

    }
    cout << "|\033[100m_____________________________________________________________________________\033[0m|" << endl;
    cout << fixed << setprecision(2) << "|\033[40m                   Distance travelled: " << minimalTrip.second;
    for (int i = 0; i < 42 - to_string(minimalTrip.second).length(); i++)
        cout << ' ';
    cout << "\033[0m|" << endl;
    cout << "|\033[40m_____________________________________________________________________________\033[0m|" << endl;
    cout << "|\033[40m [n]Next                  [p]Previous                  [q]Go Back            \033[0m|" << endl;
    cout << "|\033[40m_____________________________________________________________________________\033[0m|" << endl;
}


