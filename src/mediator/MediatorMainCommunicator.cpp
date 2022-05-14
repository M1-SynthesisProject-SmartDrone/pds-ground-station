#include "MediatorMainCommunicator.h"

#include "util/memory_utils.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

MediatorMainCommunicator::MediatorMainCommunicator(std::string host, uint16_t listenPort, uint16_t sendPort):
    m_channel(host, listenPort, sendPort)
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
    auto response = m_channel.sendAndReceive(make_unique<TrSave_MediatorRequest>(), responseType);
    return memoryUtils::static_unique_pointer_cast<TrSave_MediatorResponse>(move(response));
}

void MediatorMainCommunicator::registerData(std::unique_ptr<TrRegister_MediatorRequest> registerRequest)
{
    // No response to wait for
    m_channel.sendRequest(move(registerRequest));
}

unique_ptr<TrEndSave_MediatorResponse> MediatorMainCommunicator::endRecord()
{
    auto responseType = MEDIATOR_MESSAGE_TYPE::RESP_TR_SAVE;
    auto response = m_channel.sendAndReceive(make_unique<TrEndSave_MediatorRequest>(m_currentTripName), responseType);
    return memoryUtils::static_unique_pointer_cast<TrEndSave_MediatorResponse>(move(response));
}
