//
// Created by franciscocardoso on 31-12-2022.
//

#ifndef AERIALTRANSPORTATION_SHOW_H
#define AERIALTRANSPORTATION_SHOW_H

#include <iostream>
#include "../MenuItem.h"
using namespace std;

class Show : public MenuItem{
private:
public:

    Show(int& currMenuPage, Database& database);
    virtual void execute() = 0;

    template<typename Name>
    void draw(vector<Name> data){
        system("clear");
        int start = 0;
        vector<int> starts;
        int previous_start = -1;
        int end;
        int currentPage = 1;
        while(start>=0 && start < data.size()){
            system("clear");
            bool cond = false;
            for(int s : starts){
                if(s == start) cond = true;
            }
            if(!cond) starts.push_back(start);
            end = start + 15;
            if(end >= data.size()) end = data.size();
            if(currentPage <= 9){
                cout << " _______________________________________________________________________________\n";
                cout << "|                                  Page: "<< currentPage <<"                                      |\n";
            }
            else{
                cout << " _______________________________________________________________________________    \n";
                cout << "|                                  Page: "<< currentPage <<"                                     |\n";
            }
            cout << "|_______________________________________________________________________________|\n";
            cout << "|                                                                               |\n";
            while(start < end){
                data.at(start).print();
                start++;
            }

            string option;
            bool c = true;
            cout << "|-------------------------------------------------------------------------------|\n";
            cout << "| [1] Next page \t\t\t\t\t\t\t\t|\n| [2] Previous page\t\t\t\t\t\t\t\t|\n| [3] Go back\t\t\t\t\t\t\t\t\t|\n";
            cout << "|_______________________________________________________________________________|\n";
            cout << "Choose an option: ";
            while (c) {
                cin >> option;
                if (option.length() == 1 && isdigit(option[0])) {
                    switch (option[0]) {
                        case '1':
                            previous_start++;
                            currentPage++;
                            c = false;
                            break;
                        case '2':
                            if (previous_start < 0) start = -1;
                            else start = starts.at(previous_start);
                            previous_start--;
                            currentPage--;
                            c = false;
                            break;
                        case '3':
                            start = -1;
                            c = false;
                            break;
                    }
                }
                if(c) cout << "Choose a valid option: ";
            }
        }
    };


};


#endif //AERIALTRANSPORTATION_SHOW_H
