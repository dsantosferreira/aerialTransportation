#ifndef AERIALTRANSPORTATION_AIRPORT_H
#define AERIALTRANSPORTATION_AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
    string code, name, city, country;
    float latitude, longitude;

public:
    Airport(string code, string name, string city, string country, float latitude, float longitude);

};


#endif