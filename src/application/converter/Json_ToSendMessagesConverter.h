#ifndef __JSON_TOSENDMESSAGESCONVERTER_H__
#define __JSON_TOSENDMESSAGESCONVERTER_H__

#include <string>
#include <functional>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "application/message/tosend/toSend_headers.h"

class Json_ToSendMessagesConverter
{
private:
public:
    Json_ToSendMessagesConverter();
    ~Json_ToSendMessagesConverter();

    std::string convertToSendMessage(Abstract_ApplicationToSendMessage* message);
};

#endif // __JSON_TOSENDMESSAGESCONVERTER_H__