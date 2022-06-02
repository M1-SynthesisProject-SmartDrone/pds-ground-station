#ifndef __COORDINATES_UTILS_H__
#define __COORDINATES_UTILS_H__

#include <math.h>

namespace coordinatesUtils
{
    constexpr int EARTH_RADIUS = 6371; 

    void polarToCartesian(float lat, float lon, float alt, float& x, float& y, float& z)
    {
        x = EARTH_RADIUS * cos(lat) * cos(lon);
        y = EARTH_RADIUS * cos(lat) * sin(lon);
        z = alt * 1000;
    }
}

#endif // __COORDINATES_UTILS_H__