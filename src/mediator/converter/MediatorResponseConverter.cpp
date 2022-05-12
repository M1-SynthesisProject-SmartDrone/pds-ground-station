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