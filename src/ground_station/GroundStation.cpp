#include "GroundStation.h"

#include <loguru/loguru.hpp>

#include "drone/DroneCommunicator.h"

#include "application/message/received/recevied_headers.h"
#include "application/message/tosend/toSend_headers.h"

using namespace std;

GroundStation::GroundStation(
    ConfigParams params,
    std::unique_ptr<ApplicationMediator> applicationMediator,
    std::shared_ptr<DroneCommunicator> droneCommunicator
): m_params(params)
{
    m_applicationMediator = move(applicationMediator);
    m_droneCommunicator = move(droneCommunicator);
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

void GroundStation::handleAckMessage()
{
    m_applicationMediator->sendMessage(make_unique<Ack_MessageToSend>(true));
}

void GroundStation::handleDroneInfosMessage()
{
    m_applicationMediator->sendMessage(m_droneCommunicator->fetchDroneInfos(m_inRecordState));
}

void GroundStation::handleRecordMessage(Record_MessageReceived* message)
{
    if (message->record == m_inRecordState)
    {
        m_applicationMediator->sendMessage(make_unique<Record_MessageToSend>(false, "Already in wanted record state"));
        return;
    }

    if (message->record)
    {
        // Send the command and start the thread
        
        m_inRecordState = true;
    }
    else
    {

        m_inRecordState = false;
    }
}

void GroundStation::handleStartDroneMessage(Start_MessageReceived* message)
{
    try
    {
        if (message->startDrone)
        {
            m_droneCommunicator->arm();
            m_applicationMediator->sendMessage(make_unique<StartDrone_MessageToSend>(true));
        }
        else
        {
            m_droneCommunicator->disarm();
            m_applicationMediator->sendMessage(make_unique<StartDrone_MessageToSend>(true));
        }
    }
    catch (const std::exception& e)
    {
        LOG_F(ERROR, "Error while handling arm command : %s", e.what());
        m_applicationMediator->sendMessage(make_unique<StartDrone_MessageToSend>(false, "Error while handling arm command"));
    }
}

void GroundStation::handleManualControlMessage(Manual_MessageReceived* message)
{
    try
    {
        m_droneCommunicator->control(
            message->leftMove,
            message->forwardMove,
            message->motorPower,
            message->leftRotation
        );
    }
    catch (const std::exception& e)
    {
        LOG_F(ERROR, "Error while handling manual control command : %s", e.what());
    }
}

void GroundStation::askStopRunning()
{
    m_isRunning = false;
}