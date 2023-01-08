#ifndef AERIALTRANSPORTATION_AIRPORT_H
#define AERIALTRANSPORTATION_AIRPORT_H

#include <string>

#include "Coordinate.h"

#include <iostream>

using namespace std;

class Airport
{
private:
    /** @var Airport's code. Each airport has a unique code */
    string code;

    /** @var Airport's name */
    string name;

    /** @var Airport's city */
    string city;

    /** @var Airport's country */
    string country;

    /** @var Airport's coordinate */
    Coordinate coordinate;

public:
    Airport(string code);
    Airport(string code, string name, string city, string country, float latitude, float longitude);
    string getCode() const;
    string getName() const;

    string getCity() const;
    string getCountry() const;
    Coordinate getCoordinate() const;

    void print() const;
};

struct airportHash
{
    int operator()(const Airport &airport) const
    {
        int hash = 0;
        string airportCode = airport.getCode();
        for (int i = 0; i < airportCode.size(); i++)
        {
            hash += airportCode[i] * (i + 1);
        }
        return hash;
    }

    bool operator()(const Airport &airport1, const Airport &airport2) const
    {
        return airport1.getCode() == airport2.getCode();
    }
};

#endif