#ifndef __ANDROIDMEDIATOR_H__
#define __ANDROIDMEDIATOR_H__

#include <memory>

#include "network/ReplierUDPSocket.h"
#include "application/converter/Abstract_ApplicationMessageConverter.h"
#include "application/message/received/Abstract_ApplicationReceivedMessage.h"
#include "application/message/tosend/Abstract_ApplicationToSendMessage.h"

/**
 * This class ensures the communication process between the ground station
 * (this application) and the remote control one (the smartphone).
 */
class ApplicationMediator
{
private:
    std::unique_ptr<ReplierUDPSocket> m_socket;
    std::unique_ptr<Abstract_ApplicationMessageConverter> m_converter;

    const int BUFFER_SIZE = 4096;
public:
    ApplicationMediator(
        uint16_t receivePort,
        uint16_t sendPort,
        std::unique_ptr<Abstract_ApplicationMessageConverter> m_converter
    );
    ~ApplicationMediator();

    void sendMessage(std::unique_ptr<Abstract_ApplicationToSendMessage> messageToSend);

    std::unique_ptr<Abstract_ApplicationReceivedMessage> receiveMessage();
};

#endif // __ANDROIDMEDIATOR_H__