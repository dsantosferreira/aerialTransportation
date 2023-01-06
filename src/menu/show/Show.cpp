//
// Created by franciscocardoso on 31-12-2022.
//

#include "Show.h"
/**
 * @brief Constructor of Show a class that extends MenuItem
 * @param currMenuPage the current page of the menu
 * @param database database that stores all the information
 */
Show::Show(int &currMenuPage, Database &database) : MenuItem(currMenuPage, database) {}
