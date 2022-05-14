#ifndef __MEDIATORCHANNEL_H__
#define __MEDIATORCHANNEL_H__

#include <memory>
#include <string>

#include "network/HostUdpSocket.h"
#include "mediator/messages/requests/Abstract_MediatorRequest.h"
#include "mediator/messages/responses/Abstract_MediatorResponse.h"
#include "mediator/converter/MediatorResponseConverter.h"

/**
 * Permits to handle request and responses from the comminucator.
 */
class MediatorChannel
{
private:
    std::unique_ptr<HostUdpSocket> m_socket;
    MediatorResponseConverter m_converter;    

public:
    MediatorChannel(std::string host, uint16_t listenPort, uint16_t sendPort);
    ~MediatorChannel();

    void sendRequest(std::unique_ptr<Abstract_MediatorRequest> request);
    std::unique_ptr<Abstract_MediatorResponse> receiveResponse();
    std::unique_ptr<Abstract_MediatorResponse> sendAndReceive(std::unique_ptr<Abstract_MediatorRequest> request);
    
    /**
     * This is a simple wrapper of sendAndReceive that will throw an exception
     * if the wanted response type is not the same
     */
    std::unique_ptr<Abstract_MediatorResponse> sendAndReceive(
        std::unique_ptr<Abstract_MediatorRequest> request, 
        MEDIATOR_MESSAGE_TYPE wantedResponseType
    );
};

#endif // __MEDIATORCHANNEL_H__