#ifndef AERIALTRANSPORTATION_AIRLINE_H
#define AERIALTRANSPORTATION_AIRLINE_H

#include <string>
#include <iostream>
using namespace std;

class Airline
{
private:

    /** @var Airline's code. Each airline has a unique code*/
    string code;

    /** @var Airline's name*/
    string name;

    /** @var Airline's callsign. The callsign is like a nickname for the airline. An airline can have no callsign*/
    string callSign;

    /** @var Airline's country*/
    string country;

public:
    Airline(string code);
    Airline(string code, string name, string callSign, string country);
    string getCode() const;
    string getName() const;
    void print() const;
};

struct airlineHash
{
    int operator()(const Airline &airline) const
    {
        int hash = 0;
        string airlineCode = airline.getCode();
        for (int i = 0; i < airlineCode.size(); i++)
        {
            hash += airlineCode[i] * i;
        }
        return hash;
    }

    bool operator()(const Airline &airline1, const Airline &airline2) const
    {
        return airline1.getCode() == airline2.getCode();
    }
};

#endif
