#include "numconvert_utils.h"

#include <sstream>

std::string numConvertUtils::coordIntToString(int coordinate)
{
    int integerPart = coordinate / 10000000;
    int decimalPart = coordinate % 10000000;
    std::stringstream ss;
    ss << integerPart << "." << decimalPart;
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
