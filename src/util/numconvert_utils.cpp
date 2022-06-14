#include "numconvert_utils.h"

#include <sstream>
#include <math.h>
#include <iomanip>
#include <iostream>

std::string numConvertUtils::coordIntToString(int coordinate)
{
    // Treat the "negative" part afterwards
    bool isNegative = coordinate < 0;
    coordinate = abs(coordinate);
    int integerPart = coordinate / 10000000;
    int decimalPart = coordinate % 10000000;
    std::stringstream ss;
    if (isNegative)
    {
        ss << "-";
    }
    // format decimal part with leading zeroes
    ss << integerPart << "." << std::setfill('0') << std::setw(7) << decimalPart;
    return ss.str();
}

float numConvertUtils::coordIntToFloat(int coordinate)
{
    return (float)coordinate / 10000000.0f;
}

float numConvertUtils::angleIntToFloat(int angle)
{
    return (float)angle / 100.0f;
}
