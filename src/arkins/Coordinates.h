#ifndef __COORDINATES_H__
#define __COORDINATES_H__

#include "util/numconvert_utils.h"
#include "util/coordinates_utils.h"

/**
 * A simple point in space defined in polar coordinates, 
 * along the altitude and the rotation of it.
 */
struct Coordinates
{
    // ==== POLAR COORDNIATES ====
    float latitude;
    float longitude;
    int altitude;

    // ==== CARTHESIAN COORDINATES ====
    float x;
    float y;
    float z;

    float rotation;


    /**
     * Converts from the stored format (all ints) to the wanted one 
     * (angle in decimal format for example), then calculate cartesian coordinates.
     */
    Coordinates(int latitude, int longitude, int altitude, int rotation)
    {
        this->latitude = numConvertUtils::coordIntToFloat(latitude);
        this->longitude = numConvertUtils::coordIntToFloat(longitude);
        this->altitude = altitude;
        this->rotation = numConvertUtils::angleIntToFloat(rotation);

        coordinatesUtils::polarToCartesian(this->latitude, this->longitude, this->altitude,
            this->x, this->y, this->z);
    }
};


#endif // __COORDINATES_H__