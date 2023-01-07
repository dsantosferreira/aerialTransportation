//
// Created by franciscocardoso on 07-01-2023.
//

#include "ShowAirport.h"

ShowAirport::ShowAirport(int &currMenuPage, Database &database1) : MenuItem(currMenuPage, database1) {
}

void ShowAirport::execute() {
    system("clear");
    cout << "\033[32m Enter the code or the name  of the airport you want to find: ";
    string s;
    cin>>s;
    string d;
    getline(cin,d);
    s+=d;

    if (s.length() == 3) {
        if (database.getAirports().find(Airport(s)) != database.getAirports().end()) {
            cout << "\033[0m _________________________________________________________________________________________"
                 << endl;
            cout << "|\033[100m ";
            Airport airport = database.getAirport(s);
            cout << airport.getCode() << "| " << airport.getName() << "| " << airport.getCountry() << "-"
                 << airport.getCity();
            for (int i = 0;
                 i < 80 - airport.getName().length() - airport.getCity().length() - airport.getCountry().length(); i++)
                cout << " ";
            cout << "\033[0m|" << endl
                 << "|\033[100m_________________________________________________________________________________________\033[0m|"
                 << endl;
            cout << "\033[0m" << endl;
            cout << endl << "\033[32mEnter anything to go back: ";
            cin >> s;
            return;
        }
    }
        for (Airport airport: database.getAirports()) {
            if (airport.getName() == s) {
                cout << "\033[0m _________________________________________________________________________________________"
                     << endl;
                cout << "|\033[100m ";

                cout << airport.getCode() << "| " << airport.getName() << "| " << airport.getCountry() << "-"
                     << airport.getCity();
                for (int i = 0;
                     i < 80 - airport.getName().length() - airport.getCity().length() - airport.getCountry().length(); i++)
                    cout << " ";
                cout << "\033[0m|" << endl
                     << "|\033[100m_________________________________________________________________________________________\033[0m|"
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