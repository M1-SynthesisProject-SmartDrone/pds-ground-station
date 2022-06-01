#ifndef __NUMCONVERT_UTILS_H__
#define __NUMCONVERT_UTILS_H__

#include <string>
#include <sstream>

namespace numConvertUtils
{

    /**
     * Converts a coordinate from the integer representation to the deg7 format.
     * For example, the integer '123456789' will produce string "12.3456789".
     * Another example : integer '48562147' will produce string "4.8562147"
     */
    std::string coordIntToString(int coordinate)
    {
        int integerPart = coordinate / 10000000;
        int decimalPart = coordinate % 10000000;
        std::stringstream ss;
        ss << integerPart << "." << decimalPart;
        return ss.str();
    }

    /**
     * Converts a coordinate from the integer representation to a double 
     * following the deg7 format.
     * This will results in numbers approching strings created by 
     * "convertIntToString" function (not as precise as we lose precision with floating numbers).
     */
    double coordIntToDouble(int coordinate)
    {
        return (double) coordinate / 10000000.0;
    }

    /**
     * Converts an angle represented in a number between 0 and 36499 to 
     * a number bewteen 0.0 and 364.99
     */
    double angleIntToDouble(int angle)
    {
        return (double) angle / 100.0;
    }
}

#endif // __NUMCONVERT_UTILS_H__