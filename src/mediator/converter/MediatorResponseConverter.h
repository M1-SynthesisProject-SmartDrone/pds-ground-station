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

    const std::unordered_map<std::string, MEDIATOR_MESSAGE_TYPE> TYPE_FROM_STR {
        {"RESP_TR_SAVE", MEDIATOR_MESSAGE_TYPE::RESP_TR_SAVE},
        {"RESP_END_TR_SAVE", MEDIATOR_MESSAGE_TYPE::RESP_END_TR_SAVE}
    };
};

#endif // __MEDIATORRESPONSECONVERTER_H__