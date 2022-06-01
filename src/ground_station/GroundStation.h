#ifndef __GROUNDSTATION_H__
#define __GROUNDSTATION_H__

#include "application/network/ApplicationMediator.h"
#include "drone/DroneCommunicator.h"

#include "application/message/received/recevied_headers.h"

#include "config/ConfigParams.h"

#include "threads/RegisterPath_ThreadClass.h"
#include "config/ConfigParams.h"
#include "mediator/MediatorMainCommunicator.h"

/**
 * The main class that will handle everything in the server
 */
class GroundStation
{
private:
    bool m_isRunning = true;

    ConfigParams m_params;

    std::unique_ptr<ApplicationMediator> m_applicationMediator;
    std::shared_ptr<MediatorMainCommunicator> m_mediatorMainCommunicator;
    std::shared_ptr<DroneCommunicator> m_droneCommunicator;

    std::unique_ptr<RegisterPath_ThreadClass> m_threadRegister = nullptr;

    void handleMessage(std::unique_ptr<Abstract_ApplicationReceivedMessage> message);
    void handleAckMessage();
    void handleDroneInfosMessage();
    
    
    void handleRecordMessage(Record_MessageReceived* message);
    bool isRecording();
    void startRecord();
    void endRecord();

    void handleStartDroneMessage(Start_MessageReceived* message);
    void handleManualControlMessage(Manual_MessageReceived* message);

    void handlePathListMessage(PathList_MessageReceived* message);
    void handlePathOneMessage(PathOne_MessageReceived* message);
    void handlePathLaunchMessage(PathLaunch_MessageReceived* message);
public:
    GroundStation(
        ConfigParams params,
        std::unique_ptr<ApplicationMediator> applicationMediator,
        std::shared_ptr<MediatorMainCommunicator> mediatorMainCommunicator,
        std::shared_ptr<DroneCommunicator> droneCommunicator
    );
    ~GroundStation();

    /**
     * The main entry-point method. This is gobally an infinite while loop
     */
    void run();

    void askStopRunning();
};

#endif // __GROUNDSTATION_H__