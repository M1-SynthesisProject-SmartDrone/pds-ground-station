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
    float latitude = 0.f;
    float longitude = 0.f;
    int altitude = 0.f;

    // ==== CARTHESIAN COORDINATES ====
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;

    float rotation = 0.f;

    // For calculation 
    float attraction = 0.f;
	float distance_to_drone = 0.f;

    Coordinates()
    {}

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

    void update(int latitude, int longitude, int altitude, int rotation)
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