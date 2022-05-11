#ifndef __GROUNDSTATION_H__
#define __GROUNDSTATION_H__

#include "application/network/ApplicationMediator.h"

#include "application/message/received/Record_MessageReceived.h"
#include "application/message/received/Manual_MessageReceived.h"
#include "application/message/received/Start_MessageReceived.h"

/**
 * The main class that will handle everything in the server
 */
class GroundStation
{
private:
    bool m_isRunning = true;
    std::unique_ptr<ApplicationMediator> m_applicationMediator;
    std::unique_ptr<DroneCommunicator> m_droneCommunicator;

    void handleMessage(std::unique_ptr<Abstract_ApplicationReceivedMessage> message);
    void handleAckMessage();
    void handleDroneInfosMessage();
    void handleRecordMessage(Record_MessageReceived* message);
    void handleStartDroneMessage(Start_MessageReceived* message);
    void handleManualControlMessage(Manual_MessageReceived* message);
public:
    GroundStation(
        std::unique_ptr<ApplicationMediator> applicationMediator,
        std::unique_ptr<DroneCommunicator> droneCommunicator
    );
    ~GroundStation();

    /**
     * The main entry-point method. This is gobally an infinite while loop
     */
    void run();

    void askStopRunning();
};

#endif // __GROUNDSTATION_H__