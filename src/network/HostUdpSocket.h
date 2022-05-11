#ifndef __HOSTUDPSOCKET_H__
#define __HOSTUDPSOCKET_H__

#include "network/UDPSocket.h"

/**
 * An wrapper of the udp socket class when user knows
 * where to send and receive data from.
 */
class HostUdpSocket : public UDPSocket
{
private:
    const int BUFFER_SIZE = 4096;

    sockaddr_in m_hostAddr;
    uint16_t m_sendPort;
public:
    /**
    * If send port is equals to "0", the value will be set to the listen port
    */
    HostUdpSocket(std::string host, uint16_t listenPort, uint16_t sendPort = 0);
    ~HostUdpSocket();

    // Low level methods
    int receive(char* buffer, int bufferLength, int flags = 0);
    void send(const char* msg, int msgLength, int flags = 0);

    // Higher level methods
    std::string receive(int flags = 0);
    void send(std::string message, int flags = 0);
    std::string receiveAndWaitAnswer(std::string message, int flags = 0);
};

#endif // __HOSTUDPSOCKET_H__