#ifndef __ARKINS_H__
#define __ARKINS_H__

#include <vector>

#include "Coordinates.h"

class Arkins
{
private:
    std::vector<Coordinates> attractivePoints;
    std::vector<Coordinates> repulsivePoints;
    std::vector<Coordinates> tangentialPoints;
    // uniform

public:
    Arkins(
        std::vector<Coordinates> attractivePoints,
        std::vector<Coordinates> repulsivePoints = {},
        std::vector<Coordinates> tangentialPoints = {}
        // uniform
    );
    ~Arkins();
};

#endif // __ARKINS_H__