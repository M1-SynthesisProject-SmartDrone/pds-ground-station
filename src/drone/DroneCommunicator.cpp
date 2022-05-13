#include "DroneCommunicator.h"

#include <chrono>
#include <functional>
#include <thread>

#include <loguru/loguru.hpp>
#include "channels/channels.h"
#include "util/base_64.h"

using namespace std;

DroneCommunicator::DroneCommunicator()
{}

DroneCommunicator::~DroneCommunicator()
{}

bool DroneCommunicator::isArmed()
{
    return pdsChannels::state.chars[0] == 1;
}

void DroneCommunicator::arm(int timeoutMs)
{
    LOG_F(INFO, "Try to arm the drone");
    if (isArmed())
    {
        // Already armed
        return;
    }
    pdsChannels::controlCommands.chars[0] = 1;
    
    // Wait until the field is changed. If it is not the case, timeout !
    auto startTime = chrono::steady_clock::now();
    while(!isArmed())
    {
        auto checkpointTime = chrono::steady_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(checkpointTime - startTime).count();
        if (elapsedTime > timeoutMs)
        {
            throw runtime_error("Timeout exedeed !");
        }
        this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    // We want to reset the command field in order to be able to use it after
    pdsChannels::controlCommands.chars[0] = 0;
}

void DroneCommunicator::disarm(int timeoutMs)
{
    LOG_F(WARNING, "Try to disarm the drone");
    if (!isArmed())
    {
        // Already disarmed
        return;
    }
    pdsChannels::controlCommands.chars[1] = 1;
    
    // Wait until the field is changed. If it is not the case, timeout !
    auto startTime = chrono::steady_clock::now();
    while(isArmed())
    {
        auto checkpointTime = chrono::steady_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(checkpointTime - startTime).count();
        if (elapsedTime > timeoutMs)
        {
            throw runtime_error("Timeout exedeed !");
        }
        this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    // We want to reset the command field in order to be able to use it after
    pdsChannels::controlCommands.chars[1] = 0;
}

void DroneCommunicator::control(float x, float y, float z, float r)
{
    pdsChannels::controlMotors.floats[0] = x;
    pdsChannels::controlMotors.floats[1] = y;
    pdsChannels::controlMotors.floats[2] = z;
    pdsChannels::controlMotors.floats[3] = r;
}

unique_ptr<DroneInfos_MessageToSend> DroneCommunicator::fetchDroneInfos(bool isRecording)
{
    auto infos = make_unique<DroneInfos_MessageToSend>();
    infos->alt = pdsChannels::globalPosition.ints32[2];
    infos->batteryRemaining = pdsChannels::battery.ints32[4];
    infos->isArmed = isArmed();
    infos->isRecording = isRecording;
    infos->lat = pdsChannels::globalPosition.ints32[0];
    infos->lon = pdsChannels::globalPosition.ints32[1];
    infos->relativeAlt = pdsChannels::globalPosition.ints32[3];
    infos->vx = pdsChannels::globalPosition.ints32[4];
    infos->vy = pdsChannels::globalPosition.ints32[5];
    infos->vz = pdsChannels::globalPosition.ints32[6];
    infos->yawRotation = pdsChannels::globalPosition.ints32[7];
    return move(infos);
}

unique_ptr<TrRegister_MediatorRequest> DroneCommunicator::fetchRegisterData(bool isCheckpoint)
{
    auto data = make_unique<TrRegister_MediatorRequest>();

    data->altitude = pdsChannels::globalPosition.ints32[2];
    data->batteryRemaining = pdsChannels::battery.ints32[4];
    data->isCheckpoint = isCheckpoint;
    data->latitude = pdsChannels::globalPosition.ints32[0];
    data->longitude = pdsChannels::globalPosition.ints32[1];
    data->rotation = pdsChannels::globalPosition.ints32[7];
    data->pressure = pdsChannels::highresImu.floats[9];
    data->temperature = pdsChannels::highresImu.floats[12];

    // fetch the image
    auto imgBuffer = pdsChannels::image.uchars;
    const auto rows = pdsChannels::imageSize.uints32[0];
    const auto cols = pdsChannels::imageSize.uints32[1];
    const auto bufferLength = pdsChannels::imageSize.uints32[2];

    string encodedImage = encode_base64(imgBuffer, bufferLength);

    data->image = encodedImage;

    auto time = chrono::system_clock::now().time_since_epoch();
    data->time = chrono::duration_cast<chrono::milliseconds>(time).count();

    return move(data);
}