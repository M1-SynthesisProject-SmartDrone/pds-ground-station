#include "Autopilot_ThreadClass.h"

#include <channels/channels.h>

using namespace std;

Autopilot_ThreadClass::Autopilot_ThreadClass(
    int saveFrequency,
    int checkpointFrequency,
    std::shared_ptr<DroneCommunicator> droneComminucator,
    std::shared_ptr<MediatorMainCommunicator> mainCommunicator,
    std::shared_ptr<MediatorSecondaryCommunicator> secondaryCommunicator
) : SAVE_FREQ(saveFrequency),
CHECKPOINT_FREQUENCY(checkpointFrequency),
Abstract_ThreadClass("autopilot", 1000.0 / (double)SAVE_FREQ, 1000.0 / (double)SAVE_FREQ)
{
    m_droneCommunicator = droneComminucator;
    m_mainCommunicator = mainCommunicator;
    m_secondaryCommunicator = secondaryCommunicator;
}

Autopilot_ThreadClass::~Autopilot_ThreadClass()
{}

void Autopilot_ThreadClass::run()
{
    initRun();

    LOG_F(INFO, "Fetch all checkpoints");
    m_checkpoints = m_secondaryCommunicator->fetchAllCheckpoints();

    LOG_F(INFO, "Find first checkpoint");
    fetchNextCheckpoint();

    m_arkins = make_unique<Arkins>(m_checkpoints);

    LOG_F(INFO, "Start registering with save frequency = %dHz and checkpoint each %d points",
        SAVE_FREQ,
        CHECKPOINT_FREQUENCY
    );

    while (isRunFlag())
    {
        onStartLoop();

        m_droneCoordinates.update(
            pdsChannels::globalPosition.ints32[0],
            pdsChannels::globalPosition.ints32[1],
            pdsChannels::globalPosition.ints32[2],
            pdsChannels::globalPosition.ints32[7]
        );

        // This will will blocked here if we are in error mode
        unique_lock lock(m_mutex);
        conditionVariable.wait(lock, [this] { return this->isInErrorMode; });

        registerImage();

        bool isCheckpointReached = processAutopilot();
        if (isCheckpointReached)
        {
            onCheckpointReached();
        }
        onEndLoop();
    }
}

void Autopilot_ThreadClass::registerImage()
{
    bool isCheckpoint = false;
    if (m_cptUntilCheckpoint == 0)
    {
        isCheckpoint = true;
        m_cptUntilCheckpoint = CHECKPOINT_FREQUENCY;
    }
    try
    {
        auto request = m_droneCommunicator->fetchRegisterData(isCheckpoint);
        m_currentImage = m_droneCommunicator->fetchImageData();
        m_mainCommunicator->registerData(move(request), m_currentImage);
    }
    catch (const std::exception& e)
    {
        LOG_F(ERROR, "Error while registering data : %s", e.what());
    }

    m_cptUntilCheckpoint--;
}

void Autopilot_ThreadClass::fetchNextCheckpoint()
{
    auto checkpointTuple = m_secondaryCommunicator->fetchNextCheckpoint();
    m_currentCheckpointId = std::get<0>(checkpointTuple);
    m_currentCheckpointImage = std::get<1>(checkpointTuple);
}

bool Autopilot_ThreadClass::processAutopilot()
{
    m_arkins->process(m_droneCoordinates);
    Informations& movementInfos = m_arkins->getInfos();
    pdsChannels::controlMotors.floats[0] = movementInfos.ratioX;
    pdsChannels::controlMotors.floats[1] = movementInfos.ratioY;
    pdsChannels::controlMotors.floats[2] = movementInfos.ratioZ;
    pdsChannels::controlMotors.floats[3] = movementInfos.ratioR;
    return movementInfos.inRange;
}

void Autopilot_ThreadClass::onCheckpointReached()
{
    auto& infos = m_arkins->getInfos();
    m_arkins->deleteAttractivePoint(infos.nearestPointIndex);
    if (m_arkins->countAttractionPoints() == 0) // No point to reach anymore
    {
        LOG_F(INFO, "End of the trip reached, stop the thread");
        setRunFlag(false);
    }
    else
    {
        startImagesComparison();
        fetchNextCheckpoint();
        bool hasAnomaly = endImagesComparison();
        if (hasAnomaly)
        {
            LOG_F(INFO, "Anomaly detected, stop this thread !");
            isInErrorMode = true;
            m_mainCommunicator->startErrorMode();
        }
    }
}

void Autopilot_ThreadClass::startImagesComparison()
{

}

bool Autopilot_ThreadClass::endImagesComparison()
{
    return false;
}