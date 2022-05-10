#ifndef __DRONECOMMUNICATOR_H__
#define __DRONECOMMUNICATOR_H__

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
    

    // ==== OPERATIONS ON DRONE ====

    /**
     * Ask the drone to arm and wait for result.
     * The operation is considered a failure if the timeout is exeeded
     */
    bool arm(int timeoutMs = 1000);
};

#endif // __DRONECOMMUNICATOR_H__