//
// Created by franciscocardoso on 03-01-2023.
//

#include "Organizer.h"
Organizer::Organizer() {}
void Organizer::draw() const
{
    system("clear");
    cout<<"\033[0m";
    string display;
    display = " _____________________________________________ \n"
              "|\033[40m                Order Options                \033[0m|\n"
              "|\033[40m_____________________________________________\033[0m|\n";

    for (int i = 0; i < this->buttons.size(); i++)
    {
        display += "|\033[100m\033[37m---------------------------------------------\033[0m|\n";
        display += "|\033[100m [" + to_string(i + 1) + "] " + this->buttons[i];
        for (int j = 0; j < (39 - this->buttons[i].length()); j++)
            display += " "; // adding spaces to format the menu
        if (i < 9)
            display += ' ';
        display += "\033[0m|\n";
    }
    display += "|\033[100m_____________________________________________\033[0m|\n";
    display += "|\033[40m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\033[0m|\n";
    display += "|\033[40m_____________________________________________\033[0m|\n";
    cout << display << endl;
}
