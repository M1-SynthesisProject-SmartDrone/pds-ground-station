#include "MediatorChannel.h"

using namespace std;

MediatorChannel::MediatorChannel(std::string host, uint16_t listenPort, uint16_t sendPort)
{
    m_socket = make_unique<HostUdpSocket>(host, listenPort, sendPort);
}

MediatorChannel::~MediatorChannel()
{}

void MediatorChannel::sendRequest(unique_ptr<Abstract_MediatorRequest> request)
{
    m_socket->send(request->toJson());
}

unique_ptr<Abstract_MediatorResponse> MediatorChannel::receiveResponse()
{
    string responseStr = m_socket->receive();
    auto response = m_converter.convertResponse(responseStr);
    return unique_ptr<Abstract_MediatorResponse>();
}

unique_ptr<Abstract_MediatorResponse> MediatorChannel::sendAndReceive(unique_ptr<Abstract_MediatorRequest> request)
{
    sendRequest(move(request));
    return receiveResponse();
}

unique_ptr<Abstract_MediatorResponse> MediatorChannel::sendAndReceive(
    std::unique_ptr<Abstract_MediatorRequest> request, 
    MEDIATOR_MESSAGE_TYPE wantedResponseType)
{
    auto response = sendAndReceive(move(request));
    if (response->messageType != wantedResponseType)
    {
        stringstream ss;
        ss << "Invalid response type : wanted " << wantedResponseType << "but got " << response->messageType;
        throw runtime_error(ss.str());
    }
    return move(response);
}
