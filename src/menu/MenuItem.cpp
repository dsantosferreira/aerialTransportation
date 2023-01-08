#include "MenuItem.h"
/**Constructor of the MenuItem an abstract class that can be extended with the purpose of being an action, that way each class that extends MenuItem will have
 * a function execute that will do a different task
 * @brief Constructor of the MenuItem
 * @param currMenuPage
 * @param database
 */
MenuItem::MenuItem(int &currMenuPage, Database &database)
{
    this->currMenuPage = &currMenuPage;
    this->database = &database;
}
