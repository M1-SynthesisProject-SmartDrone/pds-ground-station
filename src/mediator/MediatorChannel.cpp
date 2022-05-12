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
    return unique_ptr<Abstract_MediatorResponse>(response);
}

unique_ptr<Abstract_MediatorResponse> MediatorChannel::sendAndReceive(unique_ptr<Abstract_MediatorRequest> request)
{
    sendRequest(move(request));
    return receiveResponse();
}
