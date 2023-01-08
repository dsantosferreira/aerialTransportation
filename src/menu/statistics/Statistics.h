#ifndef AERIALTRANSPORTATION_STATISTICS_H
#define AERIALTRANSPORTATION_STATISTICS_H

#include "../MenuItem.h"

class Statistics : public MenuItem{
private:
public:
    Statistics(int& currMenuPage, Database& database);
    void execute();
};

#endif //AERIALTRANSPORTATION_STATISTICS_H
