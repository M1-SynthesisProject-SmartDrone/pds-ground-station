#include "Json_ToSendMessagesConverter.h"

#include <loguru/loguru.hpp>
#include <algorithm>

using namespace std;

Json_ToSendMessagesConverter::Json_ToSendMessagesConverter()
{

}

Json_ToSendMessagesConverter::~Json_ToSendMessagesConverter()
{

}

std::string Json_ToSendMessagesConverter::convertToSendMessage(Abstract_ApplicationToSendMessage* message)
{
    try
    {
        return message->toJson();
    }
    catch (const std::exception& e)
    {
        LOG_F(ERROR, "Cannot convert struct to json : %s", e.what());
        throw invalid_argument("Cannot convert struct to json");
    }
}
