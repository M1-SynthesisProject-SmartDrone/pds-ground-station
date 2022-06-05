#include "MediatorMainCommunicator.h"

#include "util/memory_utils.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

MediatorMainCommunicator::MediatorMainCommunicator(std::string host, uint16_t port) :
    m_channel(host, port)
{

}

MediatorMainCommunicator::~MediatorMainCommunicator()
{}

// Create a name of type "Trip 01/03/2023 12:32:55"
string createTripName()
{
    auto t = time(nullptr);
    // returns a pointer to an internal data structure, do not need to delete it !
    auto tm = localtime(&t);
    stringstream ss;
    ss << "Trip " << put_time(tm, "%d/%m/%Y %H:%M:%S");
    return ss.str();
}

unique_ptr<TrSave_MediatorResponse> MediatorMainCommunicator::startRecord()
{
    m_currentTripName = createTripName();

    auto responseType = MEDIATOR_MESSAGE_TYPE::RESP_TR_SAVE;
    auto r = make_unique<TrSave_MediatorRequest>();
    auto response = m_channel.sendAndReceive(move(r), responseType);
    return memoryUtils::static_unique_pointer_cast<TrSave_MediatorResponse>(move(response));
}

void MediatorMainCommunicator::registerData(std::unique_ptr<TrRegister_MediatorRequest> registerRequest, std::vector<unsigned char>& imageData)
{
    auto response = m_channel.sendAndReceive(move(registerRequest), MEDIATOR_MESSAGE_TYPE::RESP_TR_REGISTER);
    auto resp = static_cast<TrRegister_MediatorResponse*>(response.get());
    if (resp->isDone)
    {
        m_channel.sendData(imageData);
        // No response on this last (big) message
    }
    else
    {
        throw runtime_error("Resp register failed : assure that the mediator is in a valid state");
    }
}

unique_ptr<TrEndSave_MediatorResponse> MediatorMainCommunicator::endRecord()
{
    auto responseType = MEDIATOR_MESSAGE_TYPE::RESP_END_TR_SAVE;
    auto response = m_channel.sendAndReceive(make_unique<TrEndSave_MediatorRequest>(m_currentTripName), responseType);
    return memoryUtils::static_unique_pointer_cast<TrEndSave_MediatorResponse>(move(response));
}

unique_ptr<PathList_MediatorResponse> MediatorMainCommunicator::fetchPathList()
{
    auto response = m_channel.sendAndReceive(make_unique<PathList_MediatorRequest>(), MEDIATOR_MESSAGE_TYPE::RESP_PATH_LIST);
    return memoryUtils::static_unique_pointer_cast<PathList_MediatorResponse>(move(response));
}

unique_ptr<PathOne_MediatorResponse> MediatorMainCommunicator::fetchOnePath(long pathId)
{
    auto response = m_channel.sendAndReceive(make_unique<PathOne_MediatorRequest>(pathId), MEDIATOR_MESSAGE_TYPE::RESP_PATH_ONE);
    return memoryUtils::static_unique_pointer_cast<PathOne_MediatorResponse>(move(response));
}

void MediatorMainCommunicator::launchPath(long pathId)
{
    auto response = m_channel.sendAndReceive(make_unique<TrLaunch_MediatorRequest>(pathId), MEDIATOR_MESSAGE_TYPE::RESP_TR_LAUNCH);
    auto resp = static_cast<TrLaunch_MediatorResponse*>(response.get());
    if (!resp->isDone)
    {
        throw runtime_error("Launch path failed : assure that the mediator is in a valid state or that given id is right");
    }
}

void MediatorMainCommunicator::startErrorMode()
{
    m_channel.sendAndReceive(make_unique<TrError_MediatorRequest>(), MEDIATOR_MESSAGE_TYPE::RESP_TR_ERROR);
}

void MediatorMainCommunicator::endErrorMode()
{
    m_channel.sendAndReceive(make_unique<TrEndError_MediatorRequest>(), MEDIATOR_MESSAGE_TYPE::RESP_TR_ERROR);
}
