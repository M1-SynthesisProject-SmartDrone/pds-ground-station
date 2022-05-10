#include "DroneCommunicator.h"

#include <functional>
#include <chrono>

#include <loguru/loguru.hpp>
#include "channels/channels.h"

using namespace std;

DroneCommunicator::DroneCommunicator()
{}

DroneCommunicator::~DroneCommunicator()
{}

bool DroneCommunicator::isArmed()
{
    return pdsChannels::state.chars[0] == 1;
}

bool DroneCommunicator::arm(int timeoutMs)
{
    LOG_F(INFO, "Try to arm the drone");
    if (isArmed())
    {
        // Already armed
        return true;
    }
    pdsChannels::controlCommands.chars[0] = 1;
    
    // Wait until the field is changed. If it is not the case, timeout !
    bool isFinallyArmed = true;
    auto startTime = chrono::steady_clock::now();
    while(!isArmed())
    {
        auto checkpointTime = chrono::steady_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(checkpointTime - startTime).count();
        if (elapsedTime > timeoutMs)
        {
            // timeout !
            isFinallyArmed = false;
        }
    }
    // We want to reset the command field in order to be able to use it after
    pdsChannels::controlCommands.chars[0] = 0;
    return isFinallyArmed;