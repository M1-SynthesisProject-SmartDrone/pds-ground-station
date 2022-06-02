#include "Arkins.h"

Arkins::Arkins(
    std::vector<Coordinates> attractivePoints,
    std::vector<Coordinates> repulsivePoints,
    std::vector<Coordinates> tangentialPoints): 
        attractivePoints(attractivePoints), 
        repulsivePoints(repulsivePoints), 
        tangentialPoints(tangentialPoints)
{}

Arkins::~Arkins()
{}
