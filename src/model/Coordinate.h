#ifndef AERIALTRANSPORTATION_COORDINATE_H
#define AERIALTRANSPORTATION_COORDINATE_H

class Coordinate{
private:
    float latitude;
    float longitude;
public:
    Coordinate();
    Coordinate(float latitude, float longitude);
    float getLatitude() const;
    float getLongitude() const;
    float distance(Coordinate coordinate1) const;
};

#endif //AERIALTRANSPORTATION_COORDINATE_H
