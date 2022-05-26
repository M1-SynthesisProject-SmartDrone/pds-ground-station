#include "MediatorMainCommunicator.h"

#include "util/memory_utils.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

MediatorMainCommunicator::MediatorMainCommunicator(std::string host, uint16_t port):
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
    auto response = m_channel.sendAndReceive(make_unique<TrSave_MediatorRequest>(), responseType);
    return memoryUtils::static_unique_pointer_cast<TrSave_MediatorResponse>(move(response));
}

void MediatorMainCommunicator::registerData(std::unique_ptr<TrRegister_MediatorRequest> registerRequest, std::vector<unsigned char>& imageData)
{
    m_channel.sendRequest(move(registerRequest));
    m_channel.tryReceiveValidAck();
    m_channel.sendData(imageData);
    // No response on this last (big) message
}

unique_ptr<TrEndSave_MediatorResponse> MediatorMainCommunicator::endRecord()
{
    auto responseType = MEDIATOR_MESSAGE_TYPE::RESP_TR_SAVE;
    auto response = m_channel.sendAndReceive(make_unique<TrEndSave_MediatorRequest>(m_currentTripName), responseType);
    return memoryUtils::static_unique_pointer_cast<TrEndSave_MediatorResponse>(move(response));
}
