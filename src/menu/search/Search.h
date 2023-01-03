#include "../MenuItem.h"

#ifndef AERIALTRANSPORTATION_SEARCH_H
class Search : public MenuItem{
private:
public:
    Search(int& currMenuPage, Database& database);
    void execute();
};
#define AERIALTRANSPORTATION_SEARCH_H

#endif //AERIALTRANSPORTATION_SEARCH_H
