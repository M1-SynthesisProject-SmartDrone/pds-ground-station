#include "Autopilot_ThreadClass.h"

Autopilot_ThreadClass::Autopilot_ThreadClass(
    std::shared_ptr<DroneCommunicator> droneComminucator,
    std::shared_ptr<MediatorMainCommunicator> mainCommunicator,
    std::shared_ptr<MediatorSecondaryCommunicator> secondaryCommunicator):
        Abstract_ThreadClass("autopilot", 1000, 1000)
{
    m_droneComminucator = droneComminucator;
    m_mainCommunicator = mainCommunicator;
    m_secondaryCommunicator = secondaryCommunicator;
}

Autopilot_ThreadClass::~Autopilot_ThreadClass()
{}

void Autopilot_ThreadClass::run()
{
    initRun();

    LOG_F(INFO, "Fetch all checkpoints");
    
}
