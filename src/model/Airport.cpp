#include <cmath>
#include "Airport.h"

using namespace std;

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude) : coordinate(Coordinate(latitude, longitude)) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
}

string Airport::getCode() const {
    return code;
}

string Airport::getName() const {
    return name;
}


string Airport::getCountry() const {
    return country;
}

string Airport::getCity() const {
    return city;
}

Coordinate Airport::getCoordinate() const {
    return coordinate;
}

void Airport::print()const {
    cout<<this->getCode()<<"       | "<<this->getName();
    for(int i=0; i<66-this->getName().length();i++)cout<<" ";
}