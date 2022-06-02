#include "coordinates_utils.h"
#include <math.h>

void coordinatesUtils::polarToCartesian(float lat, float lon, float alt, float& x, float& y, float& z)
{
    x = EARTH_RADIUS * cos(lat) * cos(lon);
    y = EARTH_RADIUS * cos(lat) * sin(lon);
    z = alt * 1000;
}