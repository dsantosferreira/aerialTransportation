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