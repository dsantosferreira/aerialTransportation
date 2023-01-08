#include "ShowAirport.h"

/**Constructor of the class ShowAirport a class that extends MenuItem
 * @brief Constructor of the class ShowAirport
 * @param currMenuPage the current page of the menu
 * @param database the database containing all the information
 */
ShowAirport::ShowAirport(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {
}
/**Asks the user for an airport code or name and displays its code, name, country and city
 * @brief Search for an airport and displays its code, name, country and city
 * complexity: O(1) when its given the airport code O(N) when its given its name being N the number of airports
 */
void ShowAirport::execute() {
    system("clear");
    cout << "\033[32m Enter the code or the name  of the airport you want to find: ";
    string s;
    cin>>s;
    string d;
    getline(cin,d);
    s+=d;

    if (s.length() == 3) {
        if (database->getAirports().find(Airport(s)) != database->getAirports().end()) {
            cout << "\033[0m _________________________________________________________________________________________"
                 << endl;
            cout << "|\033[40m                                         Airport                                         \033[0m|"<<endl;
            cout << "|\033[40m_________________________________________________________________________________________\033[0m|"<<endl;

            cout << "|\033[100m ";
            Airport airport = database->getAirport(s);
            cout << airport.getCode() << "| " << airport.getName() << "| " << airport.getCountry() << "-"
                 << airport.getCity();
            for (int i = 0;
                 i < 80 - airport.getName().length() - airport.getCity().length() - airport.getCountry().length(); i++)
                cout << " ";
            cout << "\033[0m|" << endl;
            cout << "|\033[47m\033[30m_________________________________________________________________________________________\033[0m|"
                 << endl;
                cout << "|\033[40m_________________________________________________________________________________________\033[0m|"
                 << endl;
            cout << "\033[0m" << endl;
            cout << endl << "\033[32mEnter anything to go back: ";
            cin >> s;
            return;
        }
    }
        for (Airport airport: database->getAirports()) {
            if (airport.getName() == s) {
                cout << "\033[0m _________________________________________________________________________________________"
                     << endl;
                cout << "|\033[40m                                         Airport                                         \033[0m|"<<endl;
                cout << "|\033[40m_________________________________________________________________________________________\033[0m|"<<endl;

                cout << "|\033[100m ";
                cout << airport.getCode() << "| " << airport.getName() << "| " << airport.getCountry() << "-"
                     << airport.getCity();
                for (int i = 0;
                     i < 80 - airport.getName().length() - airport.getCity().length() - airport.getCountry().length(); i++)
                    cout << " ";
                cout << "\033[0m|" << endl;
                cout << "|\033[47m\033[30m_________________________________________________________________________________________\033[0m|"
                     << endl;
                cout << "|\033[40m_________________________________________________________________________________________\033[0m|"
                     << endl;
                cout << "\033[0m" << endl;
                cout << endl << "\033[32mEnter anything to go back: ";
                cin >> s;
                return;
            }

    }
            cout << "\033[31mAirport not found!";
            cout << endl << "\033[32mEnter anything to go back: ";
            cin >> s;
}