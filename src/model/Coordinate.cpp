#include <cmath>
#include "Coordinate.h"

Coordinate::Coordinate() {
    this->latitude=0;
    this->longitude=0;
}

Coordinate::Coordinate(float latitude, float longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}

float Coordinate::getLongitude() const {
    return longitude;
}

float Coordinate::getLatitude() const {
    return latitude;
}

float Coordinate::distance(Coordinate coordinate2) const {
    float distLongitude = (this->longitude - coordinate2.getLongitude()) * M_PI/180.0;
    float distLatitude = (this->latitude - coordinate2.getLatitude()) * M_PI/180.0;

    float radLatitude1 = this->latitude * M_PI/180.0;
    float radLatitude2 = coordinate2.getLatitude() * M_PI/180.0;

    float alpha = powf(sin(distLatitude/2), 2) + powf(sin(distLongitude/2), 2) * cos(radLatitude1) * cos(radLatitude2);

    float dist = 6371.0 * 2.0 * asin(sqrt(alpha));
    return dist;
}