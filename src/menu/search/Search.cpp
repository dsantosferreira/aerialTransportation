#include "Search.h"
#include "../Menu.h"

Search::Search(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}

bool getFloat(float &option) {
    cin >> option;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    return false;
}

bool getMaximumAirlines(int &maxAirlines) {
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

unordered_set<string> airportInput(Database& database) {
    unordered_set<string> result;
    string input;
    cout << "\033[32mIntroduce the airport code: ";
    while (true) {
        cin >> input;
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

unordered_set<string> cityInput(Database& database) {
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

unordered_set<string> locationInput(Database& database) {
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

bool orderTrips(const trip &t1, const trip &t2) {
    return t1.second < t2.second;
}

void Search::execute() {
    pair<unordered_set<string>, bool> originAirports, destAirports;
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

    trips minimalFlights = getMinimalFlights(originAirports.first, destAirports.first, airlines, maxAirlines);

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
            cout <<"\033[31m"<< input << " isn't a valid airline. Please insert a valid airline:\033[31m ";
    }
}

int Search::selectMaximumAirlines() {
    int maxAirlines;

    system("clear");
    cout << "Choose the maximum number of airlines you want to travel with: ";
    while (getMaximumAirlines(maxAirlines));
    return maxAirlines;
}

trips Search::getMinimalFlights(unordered_set<string> originAirports, unordered_set<string> destAirports, unordered_set<string> airlines, const int maxFlights) {
    Graph flights = database->getFlightsGraph();
    trips minimalTrips;
    trips currTrips;

    for (string originAirport: originAirports) {
        currTrips = flights.minFlightsBFS(originAirport, destAirports, airlines, maxFlights);

        if (currTrips.empty())
            continue;

        // Calculated flights are minimal as well
        if (minimalTrips.empty() || minimalTrips[0].first.size() == currTrips[0].first.size()) {
            minimalTrips.insert(minimalTrips.end(), currTrips.begin(), currTrips.end());
        }

        // Calculated flights are less than the ones calculated previously
        else if (minimalTrips[0].first.size() > currTrips[0].first.size()) {
            minimalTrips = currTrips;
        }

        // Else calculated flights are more than the ones calculated previously and get ignored
    }

    return minimalTrips;
}

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


