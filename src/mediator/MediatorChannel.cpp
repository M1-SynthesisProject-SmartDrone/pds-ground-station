#include "MediatorChannel.h"

#include "util/memory_utils.hpp"

using namespace std;

MediatorChannel::MediatorChannel(std::string host, uint16_t port)
{
    m_socket = make_unique<TCPSocket>();
    m_socket->connectToServer(host, port);
}

MediatorChannel::~MediatorChannel()
{}

void MediatorChannel::sendRequest(unique_ptr<Abstract_MediatorRequest> request)
{
    m_socket->sendMessage(request->toJson());
}

unique_ptr<Abstract_MediatorResponse> MediatorChannel::receiveResponse()
{
    string responseStr = m_socket->receiveMessage();
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
        ss << "Invalid response type : wanted " << (int)wantedResponseType << "but got " << (int)response->messageType;
        throw runtime_error(ss.str());
    }
    return move(response);
}

void MediatorChannel::sendData(std::vector<unsigned char>& data)
{
    // TCP allows to send all at once (will split itself the message)
    m_socket->sendMessage(data.data(), data.size());
}

void MediatorChannel::tryReceiveValidAck()
{
    auto resp = receiveResponse();
    if (resp->messageType != MEDIATOR_MESSAGE_TYPE::RESP_ACK)
    {
        stringstream ss;
        ss << "Invalid response type : wanted RESP_ACK but got " << (int)resp->messageType;
        throw runtime_error(ss.str());
    }
    auto ackResp = memoryUtils::static_unique_pointer_cast<Ack_MediatorResponse>(move(resp));
    if (!ackResp->valid)
    {
        throw runtime_error("Ack response is not valid");
    }
}

TCPSocket* MediatorChannel::getTcpSocket()
{
    return m_socket.get();
}
