#ifndef __REGISTERPATH_THREADCLASS_H__
#define __REGISTERPATH_THREADCLASS_H__

#include "Abstract_ThreadClass.h"
#include "drone/DroneCommunicator.h"
#include "mediator/MediatorMainCommunicator.h"

/**
 * This thread is handled (launched and monitored) by the GroundStation class.
 * 
 * It handles the "register" request that must be made periodically.
 */
class RegisterPath_ThreadClass : Abstract_ThreadClass
{
private:
    const int SAVE_FREQ; // Hz
    // How many register between each checkpoint
    const int CHECKPOINT_FREQUENCY;
    
    std::shared_ptr<DroneCommunicator> m_droneCommunicator;
    std::shared_ptr<MediatorMainCommunicator> m_mediatorCommunicator;

public:
    RegisterPath_ThreadClass(
        int saveFrequency,
        int checkpointFrequency,
        std::shared_ptr<DroneCommunicator> droneCommunicator,
        std::shared_ptr<MediatorMainCommunicator> mediatorCommunicator
    );
    ~RegisterPath_ThreadClass();

    /**
     * For each iteration of the run loop, we fetch the wanted drone data 
     * and send it to the Mediator.
     */
    void run();
};

#endif // __REGISTERPATH_THREADCLASS_H__