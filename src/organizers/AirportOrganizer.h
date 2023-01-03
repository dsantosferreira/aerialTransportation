//
// Created by franciscocardoso on 03-01-2023.
//

#ifndef AERIALTRANSPORTATION_AIRPORTORGANIZER_H
#define AERIALTRANSPORTATION_AIRPORTORGANIZER_H


#include "Organizer.h"

class AirportOrganizer: public Organizer
    {
        private:
        vector<function<bool(Airport,Airport)>> functions;
        public:
        AirportOrganizer();
        void organize(vector<Airport> &airports) const;
    };



#endif //AERIALTRANSPORTATION_AIRPORTORGANIZER_H
