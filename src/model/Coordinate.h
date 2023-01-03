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

<<<<<<< HEAD:src/Coordinate.h
=======


>>>>>>> eba6b3e083d0f0d1abaf52c24cb7f810f325eaae:src/model/Coordinate.h
#endif //AERIALTRANSPORTATION_COORDINATE_H
