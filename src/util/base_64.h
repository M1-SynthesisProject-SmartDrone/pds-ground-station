#ifndef __BASE_64_H__
#define __BASE_64_H__

#include <string>

namespace base64
{
    std::string encode(unsigned char* buffer, uint32_t bufferLength);
    std::string decode(std::string str);
}

#endif // __BASE_64_H__