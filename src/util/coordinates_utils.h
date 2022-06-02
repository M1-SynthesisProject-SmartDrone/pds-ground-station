#ifndef __COORDINATES_UTILS_H__
#define __COORDINATES_UTILS_H__

namespace coordinatesUtils
{
    constexpr int EARTH_RADIUS = 6371; 

    void polarToCartesian(float lat, float lon, float alt, float& x, float& y, float& z);
}

#endif // __COORDINATES_UTILS_H__