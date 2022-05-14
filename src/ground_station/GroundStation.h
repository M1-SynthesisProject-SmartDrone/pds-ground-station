#ifndef __GROUNDSTATION_H__
#define __GROUNDSTATION_H__

#include "application/network/ApplicationMediator.h"
#include "drone/DroneCommunicator.h"

#include "application/message/received/Record_MessageReceived.h"
#include "application/message/received/Manual_MessageReceived.h"
#include "application/message/received/Start_MessageReceived.h"

#include "config/ConfigParams.h"

#include "threads/RegisterPath_ThreadClass.h"
#include "config/ConfigParams.h"

/**
 * The main class that will handle everything in the server
 */
class GroundStation
{
private:
    bool m_isRunning = true;
    bool m_inRecordState = false;
    bool m_inAutopilotState = false;

    ConfigParams m_params;

    std::unique_ptr<ApplicationMediator> m_applicationMediator;
    std::shared_ptr<DroneCommunicator> m_droneCommunicator;

    RegisterPath_ThreadClass* m_threadRegister;

    void handleMessage(std::unique_ptr<Abstract_ApplicationReceivedMessage> message);
    void handleAckMessage();
    void handleDroneInfosMessage();
    
    
    void handleRecordMessage(Record_MessageReceived* message);
    void startRecord();
    void endRecord();

    void handleStartDroneMessage(Start_MessageReceived* message);
    void handleManualControlMessage(Manual_MessageReceived* message);
public:
    GroundStation(
        ConfigParams params,
        std::unique_ptr<ApplicationMediator> applicationMediator,
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