#include "GroundStation.h"

#include <loguru/loguru.hpp>

#include "drone/DroneCommunicator.h"

#include "application/message/received/recevied_headers.h"
#include "application/message/tosend/toSend_headers.h"
#include "util/numconvert_utils.h"

using namespace std;

GroundStation::GroundStation(
    ConfigParams params,
    std::shared_ptr<ApplicationMediator> applicationMediator,
    std::shared_ptr<MediatorMainCommunicator> mediatorMainCommunicator,
    std::shared_ptr<MediatorSecondaryCommunicator> mediatorSecondaryCommunicator,
    std::shared_ptr<DroneCommunicator> droneCommunicator
) : m_params(params), m_threadAutopilot()
{
    m_applicationMediator = applicationMediator;
    m_mediatorMainCommunicator = mediatorMainCommunicator;
    m_droneCommunicator = droneCommunicator;
    m_mediatorSecondaryCommunicator = mediatorSecondaryCommunicator;
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
    case MESSAGE_TYPE::REQ_PATH_LIST:
    {
        auto pathListMessage = static_cast<PathList_MessageReceived*>(message.get());
        handlePathListMessage(pathListMessage);
    }
    break;
    case MESSAGE_TYPE::REQ_PATH_ONE:
    {
        auto pathOneMessage = static_cast<PathOne_MessageReceived*>(message.get());
        handlePathOneMessage(pathOneMessage);
    }
    break;
    case MESSAGE_TYPE::REQ_PATH_LAUNCH:
    {
        auto pathLaunchMessage = static_cast<PathLaunch_MessageReceived*>(message.get());
        handlePathLaunchMessage(pathLaunchMessage);
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
        m_applicationMediator->sendMessage(make_unique<Record_MessageToSend>(true));
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
    return m_threadRegister != nullptr && m_threadRegister->isRunFlag();
}

bool GroundStation::isAutopilotLaunched()
{
    return m_threadAutopilot != nullptr && m_threadAutopilot->isRunFlag();
}

void GroundStation::startRecord()
{
    // Send the message to mediator, then start the famous thread
    auto resp = m_mediatorMainCommunicator->startRecord();
    if (!resp->isLaunched)
    {
        throw runtime_error("Start record failed : assure that the mediator is in a valid state");
    }

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
    if (m_threadAutopilot != nullptr && m_threadAutopilot->isRunFlag() && !m_threadAutopilot->hasUserRegainedControl)
    {
        LOG_F(ERROR, "Autopilot is launched and not in error mode");
        return;
    }
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

void GroundStation::handlePathListMessage(PathList_MessageReceived* message)
{
    auto pathListResp = m_mediatorMainCommunicator->fetchPathList();
    auto mobileResp = new PathList_MessageToSend();
    for (const auto& mediatorItem : pathListResp->paths)
    {
        char buffer[16] = { 0 };
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&mediatorItem.timestamp));
        PathList_Path pathItem{
            mediatorItem.name,
            mediatorItem.id,
            string(buffer)
        };
        mobileResp->paths.push_back(pathItem);
    }
    m_applicationMediator->sendMessage(unique_ptr<PathList_MessageToSend>(mobileResp));
}

void GroundStation::handlePathOneMessage(PathOne_MessageReceived* message)
{
    auto pathOneResp = m_mediatorMainCommunicator->fetchOnePath(message->pathId);

    auto mobileResp = new PathOne_MessageToSend();
    char buffer[16] = { 0 };
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&(pathOneResp->date)));
    mobileResp->date = string(buffer);
    mobileResp->id = pathOneResp->id;
    mobileResp->name = pathOneResp->name;
    mobileResp->nbCheckpoints = pathOneResp->nbCheckpoints;
    mobileResp->nbPoints = pathOneResp->nbPoints;
    mobileResp->departureAlt = to_string(pathOneResp->depAltitude);
    mobileResp->departureLon = numConvertUtils::coordIntToString(pathOneResp->depLongitude);
    mobileResp->departureLat = numConvertUtils::coordIntToString(pathOneResp->depLatitude);

    m_applicationMediator->sendMessage(unique_ptr<PathOne_MessageToSend>(mobileResp));
}

void GroundStation::handlePathLaunchMessage(PathLaunch_MessageReceived* message)
{
    try
    {
        m_droneCommunicator->arm();
        m_mediatorMainCommunicator->launchPath(message->pathId);
    }
    catch (const std::exception& e)
    {
        LOG_F(ERROR, "%s", e.what());
        m_applicationMediator->sendMessage(make_unique<PathLaunch_MessageToSend>(false, e.what()));
        return;
    }

    // If all is good, we can start the "automatic flight" thread
}

void GroundStation::handleAutopilotInfosMessage(AutopilotInfos_MessageReceived* message)
{
    // Always recording in this state
    auto droneInfos = m_droneCommunicator->fetchDroneInfos(true);
    auto infos = make_unique<AutopilotInfos_MessageToSend>();
    infos->alt = droneInfos->alt;
    infos->batteryRemaining = droneInfos->batteryRemaining;
    infos->isArmed = droneInfos->isArmed;
    infos->isRecording = droneInfos->isRecording;
    infos->lat = droneInfos->lat;
    infos->lon = droneInfos->lon;
    infos->relativeAlt = droneInfos->relativeAlt;
    infos->vx = droneInfos->vx;
    infos->vy = droneInfos->vy;
    infos->vz = droneInfos->vz;
    infos->yawRotation = droneInfos->yawRotation;

    // Add infos relative to autopilot
    infos->running = !isAutopilotLaunched();
    infos->errorMode = m_threadAutopilot->isInErrorMode;
    infos->manualControl = m_threadAutopilot->hasUserRegainedControl;
    m_applicationMediator->sendMessage(move(infos));
}

void GroundStation::handleRegainControlMessage(RegainControl_MessageReceived* message)
{
    if (!m_threadAutopilot->isInErrorMode)
    {
        m_applicationMediator->sendMessage(make_unique<RegainControl_MessageToSend>(false, "Autopilot is not in error mode"));
        return;
    }

    if (m_threadAutopilot->hasUserRegainedControl)
    {
        m_applicationMediator->sendMessage(make_unique<RegainControl_MessageToSend>(false, "User already have regained control"));
        return;
    }

    m_threadAutopilot->hasUserRegainedControl = true;
    m_threadRegister = make_unique<RegisterPath_ThreadClass>(
        m_params.pathRegister.saveFrequency,
        m_params.pathRegister.savesBetweenCheckpoints,
        m_droneCommunicator,
        m_mediatorMainCommunicator
        );
    m_threadRegister->start();
    m_applicationMediator->sendMessage(make_unique<RegainControl_MessageToSend>(true));
}

void GroundStation::handleResumeAutopilotMessage(ResumeAutopilot_MessageReceived* message)
{
    if (!m_threadAutopilot->isInErrorMode || !m_threadAutopilot->hasUserRegainedControl)
    {
        m_applicationMediator->sendMessage(make_unique<RegainControl_MessageToSend>(false, "Control was not regained"));
        return;
    }
    m_threadRegister->stop();
    try
    {
        m_mediatorMainCommunicator->endErrorMode();
        m_threadAutopilot->hasUserRegainedControl = false;
        m_threadAutopilot->isInErrorMode = false;
        m_threadAutopilot->conditionVariable.notify_all();
        m_applicationMediator->sendMessage(make_unique<RegainControl_MessageToSend>(true));
    }
    catch(const std::exception& e)
    {
        m_applicationMediator->sendMessage(make_unique<RegainControl_MessageToSend>(false, "Unknown error while resuming autopilot"));
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