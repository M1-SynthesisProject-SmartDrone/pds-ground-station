#ifndef __MEDIATORCHANNEL_H__
#define __MEDIATORCHANNEL_H__

#include <memory>
#include <vector>
#include <string>

#include "network/TCPSocket.h"
#include "mediator/messages/requests/Abstract_MediatorRequest.h"
#include "mediator/messages/responses/Abstract_MediatorResponse.h"
#include "mediator/converter/MediatorResponseConverter.h"

/**
 * Permits to handle request and responses from the comminucator.
 */
class MediatorChannel
{
private:
    std::unique_ptr<TCPSocket> m_socket;
    MediatorResponseConverter m_converter;    

public:
    MediatorChannel(std::string host, uint16_t port);
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

    /**
     * Send a big chunk of data to the server
     */
    void sendData(std::vector<unsigned char>& data);

    /**
     * Try to receive a message of type ACK and check if the content is positive.
     * This will throw an exception if all conditions are not met.
     */
    void tryReceiveValidAck();

    /**
     * If wanted to do lower-level operations.
     * The pointer is still managed and owned by the class, 
     * so don't copy or free it.
     */
    TCPSocket* getTcpSocket();

};

#endif // __MEDIATORCHANNEL_H__