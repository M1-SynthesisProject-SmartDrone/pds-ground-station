#include "HostUdpSocket.h"

#include <loguru/loguru.hpp>

using namespace std;

HostUdpSocket::HostUdpSocket(std::string host, uint16_t listenPort, uint16_t sendPort): 
    UDPSocket(), m_sendPort(sendPort)
{
    if (m_sendPort == 0)
    {
        m_sendPort = listenPort;
    }
    try
    {
        this->bindPort(listenPort);
        LOG_F(INFO, "Create UDP listener on port %d", listenPort);
    }
    catch (std::exception const& exception)
    {
        LOG_F(ERROR, "Error while opening socket : %s", exception.what());
        // cannot do anything else, stop all
        throw runtime_error(exception.what());
    }
}

HostUdpSocket::~HostUdpSocket()
{}

int HostUdpSocket::receive(char* buffer, int bufferLength, int flags)
{
    sockaddr_in sender;
    return UDPSocket::receiveMessage(buffer, bufferLength, sender, flags);
}

void HostUdpSocket::send(const char* msg, int msgLength, int flags = 0)
{
    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(m_sendPort);
    destination.sin_addr.s_addr = m_hostAddr.sin_addr.s_addr;

    if(sendto(getSocket(), msg, msgLength, flags, (struct sockaddr *)&destination, sizeof(destination)) < 0)
    {
        throw system_error(errno, system_category(), "Cannot send message");
    }
}

string HostUdpSocket::receive(int flags)
{
    char buffer[BUFFER_SIZE];
    int nbBytes = receive(buffer, BUFFER_SIZE);
    return string(buffer, nbBytes);
}

void HostUdpSocket::send(string message, int flags = 0)
{
    send(message.c_str(), message.size());
}

string HostUdpSocket::receiveAndWaitAnswer(string message, int flags)
{
    send(message);
    return receive();
}
