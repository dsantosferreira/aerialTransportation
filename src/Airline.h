#ifndef AERIALTRANSPORTATION_AIRLINE_H
#define AERIALTRANSPORTATION_AIRLINE_H

#include <string>

using namespace std;

class Airline {
private:
    string code, name, callSign, country;

public:
    Airline(string code, string name, string callSign, string country);
    string getCode() const;
    string getName() const;
};

#endif
