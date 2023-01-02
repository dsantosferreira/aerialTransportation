//
// Created by franciscocardoso on 31-12-2022.
//

#ifndef AERIALTRANSPORTATION_SHOWAIRLINE_H
#define AERIALTRANSPORTATION_SHOWAIRLINE_H


#include "Show.h"

class ShowAirline: public Show{

public:
    ShowAirline(int& currMenuPage, Database& database);
    void execute()override;

};


#endif //AERIALTRANSPORTATION_SHOWAIRLINE_H
