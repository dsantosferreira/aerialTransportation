#ifndef AERIALTRANSPORTATION_SHOW_H
#define AERIALTRANSPORTATION_SHOW_H

#include <iostream>
#include <cmath>
#include "../MenuItem.h"

using namespace std;

class Show : public MenuItem {
public:
    Show(int &currMenuPage, Database &database);

    virtual void execute() = 0;
    /** Controls the pagination of the drawn table. It allows the user to quit the menu, or jump to the next, previous or any other page directly.
     * @brief Controls the pagination of the drawn table.
     * @see show::draw(vector<Name> data, int page, int nPages)
     * @tparam Name type of the values we want to display
     * @param data the values we want to display
     * complexity O(1)
     */
    template<typename Name>
    void paginationController(vector<Name> data) {
        /* due to the template this functions had to be written here as if it was on the cpp it would not recognize the template*/
        int page = 0;
        while (page >= 0 and page < (float)data.size() / 10.0)
        {
            string option;
            draw(data,page,ceil((float)data.size()/10.0));
            bool cond = true;
            while (cond)
            {
                cout << endl
                     << "\033[32mChoose an option[n/p/q] or the number of the page you would want to go[1-"<<ceil((float)data.size()/10.0)<<"]: ";
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
                            if(test>0 and test <=ceil((float)data.size()/10.0)) {
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
    };


    /**
     * @brief Draws a table to display values, uses a system of pagination that displays 10 values per page
     * @tparam Name type of the value we want to display
     * @param data the values to display
     * @param page current page
     * @param nPages number of pages that exist
     * complexity O(1)
     */
    template<typename Name>
    void draw(vector<Name> data, int page, int nPages) {
        /* due to the template this functions had to be written here as if it was on the cpp it would not recognize the template*/
        system("clear");
        cout << "\033[0m";
        cout << " ______________________________________________________________________________" << endl;
        cout << "|\033[40m                                    Page(" << page + 1 << "/" << nPages << ")";
        for (int i = 0; i < 8 - to_string(page + 1).length() - to_string(nPages).length(); i++)
            cout << ' ';

        cout << "                           \033[0m|" << endl;
        cout << "|\033[40m------------------------------------------------------------------------------\033[0m|" << endl;
        cout << "|\033[40m Code     | Name                                                              \033[0m|" << endl;
        cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
        for (int i = 10 * page; i < 10 * page + 10; i++) {
            if (i == data.size())
                break;
            cout<<"|";
            if (i % 2 == 0)
                cout << "\033[47m"
                     << "\033[30m";
            else
                cout << "\033[100m";
            data[i].print();
            cout<<"\033[0m|"<<endl;

        }

        cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
        cout << "|\033[40m [n]Next                 [p]Previous                 [q]Go Back               \033[0m|" << endl;
        cout << "|\033[40m______________________________________________________________________________\033[0m|" << endl;
    };
};
#endif // AERIALTRANSPORTATION_SHOW_H
