#ifndef AERIALTRANSPORTATION_AIRLINE_H
#define AERIALTRANSPORTATION_AIRLINE_H

#include <string>
#include <iostream>
using namespace std;

class Airline
{
private:
    string code, name, callSign, country;

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
        return hash % 449;
    }

    bool operator()(const Airline &airline1, const Airline &airline2) const
    {
        return airline1.getCode() == airline2.getCode();
    }
};

#endif
