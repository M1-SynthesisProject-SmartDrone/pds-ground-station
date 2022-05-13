#include "MediatorResponseConverter.h"

#include <nlohmann/json.hpp>
#include <loguru/loguru.hpp>

#include "mediator/messages/responses/mediator_response_headers.h"

using namespace std;

MediatorResponseConverter::MediatorResponseConverter()
{}

MediatorResponseConverter::~MediatorResponseConverter()
{}

Abstract_MediatorResponse* MediatorResponseConverter::convertResponse(std::string message)
{
    try
    {
        auto document = nlohmann::json::parse(message);
        MEDIATOR_MESSAGE_TYPE messageType = findMessageType(document);
        return convertFromMessageType(document, messageType);
    }
    catch (exception& e)
    {
        //remove newlines if exists
        message.erase(remove(message.begin(), message.end(), '\n'), message.end());
        LOG_F(ERROR, "Cannot parse the json %s : %s", message.c_str(), e.what());
        throw invalid_argument("Json value is not parsable");
    }
}

MEDIATOR_MESSAGE_TYPE MediatorResponseConverter::findMessageType(nlohmann::json& document)
{
    if (document.contains("requestType"))
    {
        string typeStr = document["requestType"];
        const auto messageTypeIterator = TYPE_FROM_STR.find(typeStr);
        if (messageTypeIterator != TYPE_FROM_STR.end())
        {
            auto messageType = messageTypeIterator->second;
            return messageType;
        }
        else
        {
            throw runtime_error("This message type is not handled : " + typeStr);
        }
    }
    else
    {
        throw runtime_error("Cannot find type in request object");
    }
}

Abstract_MediatorResponse* MediatorResponseConverter::convertFromMessageType(nlohmann::json& document, MEDIATOR_MESSAGE_TYPE messageType)
{
    switch (messageType)
    {
    case RESP_TR_SAVE:
        return convertTrSave(document);
        break;
    case RESP_END_TR_SAVE:
        return convertTrEndSave(document);
        break;
    default:
        throw runtime_error("Cannot find converter for message type " + messageType);
        break;
    }
}

TrSave_MediatorResponse* MediatorResponseConverter::convertTrSave(nlohmann::json& document)
{
    return new TrSave_MediatorResponse(document["isLaunched"]);
}

TrEndSave_MediatorResponse* MediatorResponseConverter::convertTrEndSave(nlohmann::json& document)
{
    return new TrEndSave_MediatorResponse(document["isLaunched"]);
}