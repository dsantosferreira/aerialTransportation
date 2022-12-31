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
    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
    float distance(Airport airport2) const;
};

struct airportHash {
    int operator() (const Airport& airport) const {
        int hash = 0;
        string airportCode = airport.getCode();
        for (int i = 0; i < airportCode.size(); i++) {
            hash += airportCode[i] * (i + 1);
        }
        return hash % 3023;
    }

    bool operator() (const Airport& airport1, const Airport& airport2) const {
        return airport1.getCode() == airport2.getCode();
    }
};

#endif