#include "Json_ApplicationMessageConverter.h"

using namespace std;

Json_ApplicationMessageConverter::Json_ApplicationMessageConverter()
{
    m_receivedMessagesConverter = make_unique<Json_ReceivedMessagesConverter>();
    m_toSendMessagesConverter = make_unique<Json_ToSendMessagesConverter>();
}

Json_ApplicationMessageConverter::~Json_ApplicationMessageConverter()
{}

Abstract_ApplicationReceivedMessage* Json_ApplicationMessageConverter::convertMessageReceived(string message)
{
    return m_receivedMessagesConverter->convertMessageReceived(message);
}

string Json_ApplicationMessageConverter::convertToSendMessage(Abstract_ApplicationToSendMessage* message)
{
    return m_toSendMessagesConverter->convertToSendMessage(message);
}