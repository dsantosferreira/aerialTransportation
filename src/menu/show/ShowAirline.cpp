//
// Created by franciscocardoso on 07-01-2023.
//

#include "ShowAirline.h"
/**Constructor of the class ShowAirline  a class that extends MenuItem
 * @brief Constructor of the class ShowAirline
 * @param currMenuPage the current page of the menu
 * @param database the database containing all the information
 */
ShowAirline::ShowAirline(int &currMenuPage, Database &database): MenuItem(currMenuPage,database) {
}
/**Asks the user for an airline code or name and displays its code and name
 * @brief Search for an airline and displays its code and name
 * complexity: O(1) when its given the airline code O(N) when its given its name being N the number of airlines
 */
void ShowAirline::execute() {
    system("clear");
    cout << "\033[32m Enter the code or the name of the airline you want to find: ";
    string s;
    cin >> s;
    string d;
    getline(cin,d);
    s+=d;

    if (s.length() == 3) {
        if (database.getAirlines().find(Airline(s)) != database.getAirlines().end()) {
            cout << "\033[0m _______________________________________________________________________________"
                 << endl;
            cout << "|\033[40m                                    Airline                                    \033[0m|"
                 << endl;
            cout << "|\033[40m_______________________________________________________________________________\033[0m|"
                 << endl;
            cout << "|\033[100m ";
            Airline airline = database.getAirline(s);
            airline.print();
            cout << "\033[0m|" << endl
             << "|\033[47m"
                 << "\033[30m"
                 << "_______________________________________________________________________________\033[0m|"
                 << endl;
            cout << "|\033[40m_______________________________________________________________________________\033[0m|";
            cout << "\033[0m" << endl;
            cout << endl << "\033[32mEnter anything to go back: ";
            cin >> s;
            return;
        }
    }
    for (Airline airline: database.getAirlines()) {
        if (airline.getName() == s) {
            cout << "\033[0m _______________________________________________________________________________"
                 << endl;
            cout << "|\033[40m                                    Airline                                    \033[0m|"
                 << endl;
            cout << "|\033[40m_______________________________________________________________________________\033[0m|"
                 << endl;
            cout << "|\033[100m ";
            airline.print();
            cout << "\033[0m|" << endl
                 << "|\033[47m"
                 << "\033[30m"
                 << "_______________________________________________________________________________\033[0m|"
                 << endl;
            cout << "|\033[40m_______________________________________________________________________________\033[0m|";
            cout << "\033[0m" << endl;
            cout << endl << "\033[32mEnter anything to go back: ";
            cin >> s;
            return;
        }

    }
    cout << "\033[31mAirline not found!";
    cout << endl << "\033[32mEnter anything to go back: ";
    cin >> s;
}