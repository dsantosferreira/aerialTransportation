#ifndef AERIALTRANSPORTATION_COORDINATE_H

class Coordinate{
private:
    float latitude;
    float longitude;
public:
    Coordinate(float latitude, float longitude);
    float getLatitude() const;
    float getLongitude() const;
    float distance(Coordinate coordinate1) const;
};

#define AERIALTRANSPORTATION_COORDINATE_H

#endif //AERIALTRANSPORTATION_COORDINATE_H
