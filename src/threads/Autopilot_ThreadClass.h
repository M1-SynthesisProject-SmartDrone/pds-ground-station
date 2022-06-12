#ifndef __AUTOPILOT_THREADCLASS_H__
#define __AUTOPILOT_THREADCLASS_H__

#include "Abstract_ThreadClass.h"

#include <mutex>
#include <condition_variable>

#include "arkins/Arkins.h"
#include "drone/DroneCommunicator.h"
#include "mediator/MediatorMainCommunicator.h"
#include "mediator/MediatorSecondaryCommunicator.h"

class Autopilot_ThreadClass : public Abstract_ThreadClass
{
private:
    // ==== constants ====
    const int SAVE_FREQ; // Hz
    // How many register between each checkpoint
    const int CHECKPOINT_FREQUENCY;

    // ==== communication with entities ====
    std::shared_ptr<DroneCommunicator> m_droneCommunicator;
    std::shared_ptr<MediatorMainCommunicator> m_mainCommunicator;
    std::shared_ptr<MediatorSecondaryCommunicator> m_secondaryCommunicator;

    // ==== autopilot & image processing ====
    Coordinates m_droneCoordinates;
    std::vector<Coordinates> m_checkpoints;
    int m_currentCheckpointId;
    std::vector<unsigned char> m_currentCheckpointImage;

    std::unique_ptr<Arkins> m_arkins = nullptr; 

    // ==== image registration ====
    int m_cptUntilCheckpoint = 0;
    std::vector<unsigned char> m_currentImage;

    // ==== misc ====
    std::mutex m_mutex;

    // ==== private methods ====
    void registerImage();

    void fetchNextCheckpoint();
    
    /**
     * Return true if a checkpoint is reached
     */
    bool processAutopilot();

    void onCheckpointReached();
    
    void startImagesComparison();
    /**
     * Returns true if an anomaly is detected
     */
    bool endImagesComparison();

public:
    Autopilot_ThreadClass(
        int saveFrequency,
        int checkpointFrequency,
        std::shared_ptr<DroneCommunicator> droneComminucator,
        std::shared_ptr<MediatorMainCommunicator> mainCommunicator,
        std::shared_ptr<MediatorSecondaryCommunicator> secondaryCommunicator
    );
    ~Autopilot_ThreadClass();

    void run();

    std::condition_variable conditionVariable;
    bool isInErrorMode = false;
    bool hasUserRegainedControl = false;
};

#endif // __AUTOPILOT_THREADCLASS_H__