#ifndef __AUTOPILOT_THREADCLASS_H__
#define __AUTOPILOT_THREADCLASS_H__

#include "Abstract_ThreadClass.h"

#include "drone/DroneCommunicator.h"
#include "mediator/MediatorMainCommunicator.h"
#include "mediator/MediatorSecondaryCommunicator.h"

class Autopilot_ThreadClass : public Abstract_ThreadClass
{
private:
    std::shared_ptr<DroneCommunicator> m_droneComminucator;
    std::shared_ptr<MediatorMainCommunicator> m_mainCommunicator;
    std::shared_ptr<MediatorSecondaryCommunicator> m_secondaryCommunicator;


public:
    Autopilot_ThreadClass(
        std::shared_ptr<DroneCommunicator> droneComminucator,
        std::shared_ptr<MediatorMainCommunicator> mainCommunicator,
        std::shared_ptr<MediatorSecondaryCommunicator> secondaryCommunicator
    );
    ~Autopilot_ThreadClass();

    void run();
};

#endif // __AUTOPILOT_THREADCLASS_H__