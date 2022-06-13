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
    if (document.contains("responseType"))
    {
        string typeStr = document["responseType"];
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
    case MEDIATOR_MESSAGE_TYPE::RESP_ACK:
        return convertAck(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_TR_SAVE:
        return convertTrSave(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_END_TR_SAVE:
        return convertTrEndSave(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_TR_REGISTER:
        return convertRegister(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_TR_LAUNCH:
        return convertTrLaunch(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_PATH_LIST:
        return convertPathList(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_PATH_ONE:
        return convertPathOne(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_TR_ERROR:
        return convertTrError(document);
        break;
    case MEDIATOR_MESSAGE_TYPE::RESP_TR_END_LAUNCH:
        return convertTrEndLaunch(document);
        break;
    default:
        {
            stringstream ss;
            ss << "Cannot find converter for message type " << (int)messageType;
            throw runtime_error(ss.str());
        }
        break;
    }
}

TrSave_MediatorResponse* MediatorResponseConverter::convertTrSave(nlohmann::json& document)
{
    return new TrSave_MediatorResponse(document["isLaunched"]);
}

TrRegister_MediatorResponse* MediatorResponseConverter::convertRegister(nlohmann::json& document)
{
    return new TrRegister_MediatorResponse(document["isDone"]);
}

TrEndSave_MediatorResponse* MediatorResponseConverter::convertTrEndSave(nlohmann::json& document)
{
    return new TrEndSave_MediatorResponse(document["isDone"]);
}

Ack_MediatorResponse* MediatorResponseConverter::convertAck(nlohmann::json& document)
{
    return new Ack_MediatorResponse(document["valid"]);
}

TrLaunch_MediatorResponse* MediatorResponseConverter::convertTrLaunch(nlohmann::json& document)
{
    return new TrLaunch_MediatorResponse(document["isDone"]);
}

TrEndLaunch_MediatorResponse* MediatorResponseConverter::convertTrEndLaunch(nlohmann::json& document)
{
    return new TrEndLaunch_MediatorResponse();
}

PathList_MediatorResponse* MediatorResponseConverter::convertPathList(nlohmann::json& document)
{
    auto resp = new PathList_MediatorResponse();
    auto content = document["content"];
    for (const auto& elt : content)
    {
        RespPathList_Item item{
            elt["name"],
            elt["id"],
            elt["date"]
        };
        resp->paths.push_back(item);
    }
    return resp;
}

PathOne_MediatorResponse* MediatorResponseConverter::convertPathOne(nlohmann::json& document)
{
    auto resp = new PathOne_MediatorResponse();
    resp->name = document["name"];   
    resp->id = document["id"];
    resp->nbCheckpoints = document["nbCheckpoints"];
    resp->nbPoints = document["nbPoints"];
    resp->date = document["date"];
    resp->depLatitude = document["latitude"];
    resp->depLongitude = document["longitude"];
    resp->depAltitude = document["altitude"];
    return resp;
}

TrError_MediatorResponse* MediatorResponseConverter::convertTrError(nlohmann::json& document)
{
    return new TrError_MediatorResponse();
}