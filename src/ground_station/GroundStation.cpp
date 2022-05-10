#include "GroundStation.h"

#include <loguru/loguru.hpp>

#include "application/message/received/Manual_MessageReceived.h"
#include "application/message/received/Start_MessageReceived.h""
#include "application/message/received/Record_MessageReceived.h""

using namespace std;

GroundStation::GroundStation(std::unique_ptr<ApplicationMediator> applicationMediator)
{
    m_applicationMediator = move(applicationMediator);
}

GroundStation::~GroundStation()
{}

void GroundStation::run()
{
    LOG_F(INFO, "Entering the server main loop");
    while (m_isRunning)
    {
        try
        {
            handleMessage(m_applicationMediator->receiveMessage());
        }
        catch (const std::exception& e)
        {
            LOG_F(ERROR, "Error while running ground station : %s", e.what());
        }
    }
}

void GroundStation::handleMessage(std::unique_ptr<Abstract_ApplicationReceivedMessage> message)
{
    switch (message->messageType)
    {
    case MESSAGE_TYPE::REQ_ACK:
        handleAckMessage();
        break;
    case MESSAGE_TYPE::REQ_DRONE_INFOS:
        handleDroneInfosMessage();
        break;
    case MESSAGE_TYPE::REQ_MANUAL_CONTROL:
    {
        auto controlMessage = static_cast<Manual_MessageReceived*>(message.get());
        handleManualControlMessage(controlMessage);
    }
    break;
    case MESSAGE_TYPE::REQ_RECORD:
    {
        auto recordMessage = static_cast<Record_MessageReceived*>(message.get());
        handleRecordMessage(recordMessage);
    }
    break;
    case MESSAGE_TYPE::REQ_START_DRONE:
    {
        auto startMessage = static_cast<Start_MessageReceived*>(message.get());
        handleStartDroneMessage(startMessage);
    }
    break;
    default:
        // Unrecognized message
        throw runtime_error("Unrecognized message type : " + to_string(message->messageType));
        break;
    }
}

// TODO
void GroundStation::handleAckMessage()
{

}
void GroundStation::handleDroneInfosMessage()
{

}
void GroundStation::handleRecordMessage(Record_MessageReceived* message)
{

}
void GroundStation::handleStartDroneMessage(Start_MessageReceived* message)
{

}
void GroundStation::handleManualControlMessage(Manual_MessageReceived* message)
{

}

void GroundStation::askStopRunning()
{
    m_isRunning = false;
}