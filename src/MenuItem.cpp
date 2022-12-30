#include "MenuItem.h"

MenuItem::MenuItem(int &currMenuPage, Database &database) {
    this->currMenuPage = &currMenuPage;
    this->database = database;
}

