#ifndef __MEDIATORRESPONSECONVERTER_H__
#define __MEDIATORRESPONSECONVERTER_H__

#include <memory>
#include <functional>
#include <string>

#include <nlohmann/json.hpp>

#include "mediator/messages/responses/Abstract_MediatorResponse.h"

class MediatorResponseConverter
{
public:
    MediatorResponseConverter();
    ~MediatorResponseConverter();

    Abstract_MediatorResponse* convertResponse(std::string message);
private:

    MEDIATOR_MESSAGE_TYPE findMessageType(nlohmann::json& document);

    Abstract_MediatorResponse* convertFromMessageType(nlohmann::json& document, MEDIATOR_MESSAGE_TYPE messageType);
    // TODO

    const std::unordered_map<std::string, MEDIATOR_MESSAGE_TYPE> TYPE_FROM_STR {
        {"RESP_ACK", MEDIATOR_MESSAGE_TYPE::RESP_ACK},
        {"RESP_RECORD", MEDIATOR_MESSAGE_TYPE::RESP_RECORD}
    };
};

#endif // __MEDIATORRESPONSECONVERTER_H__