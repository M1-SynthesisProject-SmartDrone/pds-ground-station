#include "ApplicationMediator.h"

#include "application/converter/Json_ApplicationMessageConverter.h"

using namespace std;

ApplicationMediator::ApplicationMediator(
    uint16_t receivePort, 
    uint16_t sendPort,
    unique_ptr<Abstract_ApplicationMessageConverter> messageConverter
)
{
    m_socket = make_unique<ReplierUDPSocket>(receivePort, sendPort);
    m_converter = move(messageConverter);
}

ApplicationMediator::~ApplicationMediator()
{}

void ApplicationMediator::sendMessage(std::unique_ptr<Abstract_ApplicationToSendMessage> messageToSend)
{
    string toSend = m_converter->convertToSendMessage(messageToSend.get());
    m_socket->sendAsResponse(m_socket->getSendPort(), toSend.c_str(), toSend.length());
}

std::unique_ptr<Abstract_ApplicationReceivedMessage> ApplicationMediator::receiveMessage()
{
    char buffer[BUFFER_SIZE];
    int bytesRead = m_socket->receiveAndSaveSender(buffer, BUFFER_SIZE);
    if (bytesRead >= BUFFER_SIZE)
    {
        LOG_F(ERROR, "Received bigger message than buffer could handle, message truncated");
    }

    auto convertedMessage = m_converter->convertMessageReceived(string(buffer));
    return unique_ptr<Abstract_ApplicationReceivedMessage>(convertedMessage);
}
