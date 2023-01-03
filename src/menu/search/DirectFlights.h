//
// Created by franciscocardoso on 02-01-2023.
//

#ifndef AERIALTRANSPORTATION_DIRECTFLIGHTS_H
#define AERIALTRANSPORTATION_DIRECTFLIGHTS_H


#include "../MenuItem.h"

class DirectFlights: public MenuItem{
private:
    Database database;
public:
    DirectFlights(int& currMenuPage, Database& database);
    void execute()override;

};


#endif //AERIALTRANSPORTATION_DIRECTFLIGHTS_H
