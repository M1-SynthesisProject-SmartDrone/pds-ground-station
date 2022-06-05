#ifndef __MEDIATORRESPONSECONVERTER_H__
#define __MEDIATORRESPONSECONVERTER_H__

#include <memory>
#include <functional>
#include <string>

#include <nlohmann/json.hpp>

#include "mediator/messages/responses/mediator_response_headers.h"

class MediatorResponseConverter
{
public:
    MediatorResponseConverter();
    ~MediatorResponseConverter();

    Abstract_MediatorResponse* convertResponse(std::string message);
private:

    MEDIATOR_MESSAGE_TYPE findMessageType(nlohmann::json& document);

    Abstract_MediatorResponse* convertFromMessageType(nlohmann::json& document, MEDIATOR_MESSAGE_TYPE messageType);
    TrSave_MediatorResponse* convertTrSave(nlohmann::json& document);
    TrRegister_MediatorResponse* convertRegister(nlohmann::json& document);
    TrEndSave_MediatorResponse* convertTrEndSave(nlohmann::json& document);
    Ack_MediatorResponse* convertAck(nlohmann::json& document);
    TrLaunch_MediatorResponse* convertTrLaunch(nlohmann::json& document);
    PathList_MediatorResponse* convertPathList(nlohmann::json& document);
    PathOne_MediatorResponse* convertPathOne(nlohmann::json& document);
    TrError_MediatorResponse* convertTrError(nlohmann::json& document);

    const std::unordered_map<std::string, MEDIATOR_MESSAGE_TYPE> TYPE_FROM_STR {
        {"RESP_TR_SAVE", MEDIATOR_MESSAGE_TYPE::RESP_TR_SAVE},
        {"RESP_REGISTER", MEDIATOR_MESSAGE_TYPE::RESP_TR_REGISTER},
        {"RESP_END_TR_SAVE", MEDIATOR_MESSAGE_TYPE::RESP_END_TR_SAVE},
        {"ACK", MEDIATOR_MESSAGE_TYPE::RESP_ACK},
        {"RESP_TR_LAUNCH", MEDIATOR_MESSAGE_TYPE::RESP_TR_LAUNCH},
        {"RESP_PATH_LIST", MEDIATOR_MESSAGE_TYPE::RESP_PATH_LIST},
        {"RESP_ONE_PATH", MEDIATOR_MESSAGE_TYPE::RESP_PATH_ONE},
        {"ERROR_NOTIFICATION_RECEIVED", MEDIATOR_MESSAGE_TYPE::RESP_TR_ERROR}
    };
};

#endif // __MEDIATORRESPONSECONVERTER_H__