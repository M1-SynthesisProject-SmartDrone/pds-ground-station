
#include <vector>

#include "mediator/MediatorChannel.h"
#include "mediator/messages/requests/mediator_request_headers.h"
#include "mediator/messages/responses/mediator_response_headers.h"

/**
 * This communicator is responsible to send request and receive responses
 * from the secondary channel of the mediator.
 */
class MediatorSecondaryCommunicator
{
private:
    MediatorChannel m_channel;
public:
    MediatorSecondaryCommunicator(std::string host, uint16_t port);
    ~MediatorSecondaryCommunicator();
};
