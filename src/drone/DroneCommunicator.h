#ifndef __DRONECOMMUNICATOR_H__
#define __DRONECOMMUNICATOR_H__

#include "memory"

#include "application/message/tosend/DroneInfos_MessageToSend.h"

/**
 * This class is used to simply make contact with the drone
 * via the blc channels
 */
class DroneCommunicator
{
private:
public:
    DroneCommunicator();
    ~DroneCommunicator();

    // ==== ACCESSORS ====
    bool isArmed();
    std::unique_ptr<DroneInfos_MessageToSend> fetchDroneInfos(bool isRecording);
    

    // ==== OPERATIONS ON DRONE ====

    /**
     * Ask the drone to arm and wait for drone to be fully armed.
     * The operation is considered a failure if the timeout is exeeded.
     */
    void arm(int timeoutMs = 1000);
    
    /**
     * Set the commands for the drone to fly, as with a joystick
     */
    void control(float x, float y, float z, float r);
};

#endif // __DRONECOMMUNICATOR_H__