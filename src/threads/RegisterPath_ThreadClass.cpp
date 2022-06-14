#include "RegisterPath_ThreadClass.h"

#include <loguru/loguru.hpp>

#define REGISTER_PATH_DEBUG

using namespace std;

RegisterPath_ThreadClass::RegisterPath_ThreadClass(
    int saveFrequency,
    int checkpointFrequency,
    shared_ptr<DroneCommunicator> droneCommunicator,
    std::shared_ptr<MediatorMainCommunicator> mediatorCommunicator
) : SAVE_FREQ(saveFrequency), 
    CHECKPOINT_FREQUENCY(checkpointFrequency),
    Abstract_ThreadClass("register_path", 0, 0)
{
    // init here, or undefined values will be put in deadline & period
    task_deadline = task_period = 1000.0 / (double) SAVE_FREQ;
    m_droneCommunicator = droneCommunicator;
    m_mediatorCommunicator = mediatorCommunicator;
}

RegisterPath_ThreadClass::~RegisterPath_ThreadClass()
{}

void RegisterPath_ThreadClass::run()
{
    initRun();
    int cptUntilCheckpoint = 0;
    LOG_F(INFO, "Start registering with save frequency = %dHz and checkpoint each %d points", 
        SAVE_FREQ, 
        CHECKPOINT_FREQUENCY
    );

    while(isRunFlag()) {
        onStartLoop();

        bool isCheckpoint = false;
        if (cptUntilCheckpoint == 0)
        {
            isCheckpoint = true;
            cptUntilCheckpoint = CHECKPOINT_FREQUENCY;
        }


#ifdef REGISTER_PATH_DEBUG
        if (isCheckpoint)
        {
            LOG_F(INFO, "Register new checkpoint");
        }
#endif

        try
        {
            auto request = m_droneCommunicator->fetchRegisterData(isCheckpoint);
            auto imageData = m_droneCommunicator->fetchImageData();
            request->imageSize = imageData.size();
            auto start = chrono::steady_clock::now();
            m_mediatorCommunicator->registerData(move(request), imageData);
            auto end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
            LOG_F(INFO, "Image sent in %ld microseconds", elapsed);
        }
        catch(const std::exception& e)
        {
            LOG_F(ERROR, "Error while registering data : %s", e.what());
        }
        
        cptUntilCheckpoint--;
        onEndLoop();
    }   
}
