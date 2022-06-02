#ifndef __NUMCONVERT_UTILS_H__
#define __NUMCONVERT_UTILS_H__

#include <string>

namespace numConvertUtils
{

    /**
     * Converts a coordinate from the integer representation to the deg7 format.
     * For example, the integer '123456789' will produce string "12.3456789".
     * Another example : integer '48562147' will produce string "4.8562147"
     */
    std::string coordIntToString(int coordinate);

    /**
     * Converts a coordinate from the integer representation to a float
     * following the deg7 format.
     * This will results in numbers approching strings created by
     * "convertIntToString" function (not as precise as we lose precision with floating numbers).
     */
    float coordIntToFloat(int coordinate);

    /**
     * Converts an angle represented in a number between 0 and 36499 to
     * a number bewteen 0.0 and 364.99
     */
    float angleIntToFloat(int angle);
}

#endif // __NUMCONVERT_UTILS_H__