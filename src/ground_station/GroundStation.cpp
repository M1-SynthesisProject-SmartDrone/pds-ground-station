#include "GroundStation.h"

#include <loguru/loguru.hpp>

#include "drone/DroneCommunicator.h"

#include "application/message/received/recevied_headers.h"
#include "application/message/tosend/toSend_headers.h"

using namespace std;

GroundStation::GroundStation(
    ConfigParams params,
    std::unique_ptr<ApplicationMediator> applicationMediator,
    std::shared_ptr<MediatorMainCommunicator> mediatorMainCommunicator,
    std::shared_ptr<DroneCommunicator> droneCommunicator
) : m_params(params)
{
    m_applicationMediator = move(applicationMediator);
    m_mediatorMainCommunicator = mediatorMainCommunicator;
    m_droneCommunicator = droneCommunicator;
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
    LOG_F(INFO, "Exiting the server main loop");
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
        stringstream ss;
        ss << "Unrecognized message type : " << (int)message->messageType;
        throw runtime_error(ss.str());
    }
}

void GroundStation::handleAckMessage()
{
    m_applicationMediator->sendMessage(make_unique<Ack_MessageToSend>(true));
}

void GroundStation::handleDroneInfosMessage()
{
    m_applicationMediator->sendMessage(m_droneCommunicator->fetchDroneInfos(isRecording()));
}

void GroundStation::handleRecordMessage(Record_MessageReceived* message)
{
    if (!m_droneCommunicator->isArmed())
    {
        m_applicationMediator->sendMessage(make_unique<Record_MessageToSend>(false, "Drone is not armed"));
        return;
    }

    if (message->record == isRecording())
    {
        m_applicationMediator->sendMessage(make_unique<Record_MessageToSend>(false, "Already in wanted record state"));
        return;
    }

    try
    {
        if (message->record)
        {
            startRecord();
        }
        else
        {
            endRecord();
        }
    }
    catch (const std::exception& e)
    {
        stringstream ss;
        ss << "Error while handling record message : " << e.what();
        m_applicationMediator->sendMessage(make_unique<Record_MessageToSend>(false, ss.str()));
    }
}

bool GroundStation::isRecording()
{
    return m_threadRegister != nullptr;
}

void GroundStation::startRecord()
{
    // Send the message to mediator, then start the famous thread
    m_mediatorMainCommunicator->startRecord();

    m_threadRegister = make_unique<RegisterPath_ThreadClass>(
        m_params.pathRegister.saveFrequency,
        m_params.pathRegister.savesBetweenCheckpoints,
        m_droneCommunicator,
        m_mediatorMainCommunicator
        );
    m_threadRegister->start();
}

void GroundStation::endRecord()
{
    m_threadRegister->stop();
    m_mediatorMainCommunicator->endRecord();
}

void GroundStation::handleStartDroneMessage(Start_MessageReceived* message)
{
    if (m_droneCommunicator->isArmed() == message->startDrone)
    {
        m_applicationMediator->sendMessage(make_unique<StartDrone_MessageToSend>(false, "Drone is already in wanted state"));
        return;
    }

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
    LOG_F(INFO, "Ask stop on ground station");
    m_isRunning = false;

    if (m_threadRegister != nullptr)
    {
        LOG_F(INFO, "Try to stop register thread");
        endRecord();
    }

}