#ifndef __BASE_64_H__
#define __BASE_64_H__

#include <string>

std::string encode_base64(unsigned char* buffer, unsigned int bufferLength);

std::string decode_base64(std::string str);

#endif // __BASE_64_H__