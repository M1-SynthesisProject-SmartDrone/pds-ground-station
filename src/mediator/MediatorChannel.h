#ifndef __MEDIATORCHANNEL_H__
#define __MEDIATORCHANNEL_H__

#include <memory>
#include <string>

#include "network/HostUdpSocket.h"
#include "mediator/messages/requests/Abstract_MediatorRequest.h"
#include "mediator/messages/responses/Abstract_MediatorResponse.h"

/**
 * Base class for a channel (request / response from the communicator)
 */
class MediatorChannel
{
private:
    std::unique_ptr<HostUdpSocket> m_socket;

public:
    MediatorChannel(std::string host, uint16_t listenPort, uint16_t sendPort);
    ~MediatorChannel();

    void sendRequest(std::unique_ptr<Abstract_MediatorRequest> request);
    std::unique_ptr<Abstract_MediatorResponse> receiveResponse();
    std::unique_ptr<Abstract_MediatorResponse> sendAndReceive(std::unique_ptr<Abstract_MediatorRequest> request);
};

#endif // __MEDIATORCHANNEL_H__