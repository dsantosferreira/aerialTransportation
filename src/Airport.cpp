#include <cmath>
#include "Airport.h"

using namespace std;

Airport::Airport(string code, string name, string city, string country, float latitude, float longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
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

float Airport::getLatitude() const {
    return latitude;
}

float  Airport::getLongitude() const {
    return longitude;
}

float Airport::distance(Airport airport2) const {
    float distLongitude = (this->longitude - airport2.getLongitude()) * M_PI/180.0;
    float distLatitude = (this->latitude - airport2.getLatitude()) * M_PI/180.0;

    float radLatitude1 = this->latitude * M_PI/180.0;
    float radLatitude2 = airport2.getLatitude() * M_PI/180.0;

    float alpha = powf(sin(distLatitude/2), 2) + powf(sin(distLongitude/2), 2) * cos(radLatitude1) * cos(radLatitude2);

    float dist = 6371.0 * 2.0 * asin(sqrt(alpha));
    return dist;
}