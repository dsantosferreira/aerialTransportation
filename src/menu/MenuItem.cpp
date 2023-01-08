#include "MenuItem.h"

/**Constructor of the MenuItem an abstract class that can be extended with the purpose of being an action. That way each class that extends MenuItem will have
 * a function execute that will do a different task
 * @brief Constructor of the MenuItem
 * @param currMenuPage menu we are currently in
 * @param database program's database
 */
MenuItem::MenuItem(int &currMenuPage, Database &database)
{
    this->currMenuPage = &currMenuPage;
    this->database = &database;
}
