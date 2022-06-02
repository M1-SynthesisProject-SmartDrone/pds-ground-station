#ifndef __MEDIATORMAINCOMMUNICATOR_H__
#define __MEDIATORMAINCOMMUNICATOR_H__

#include <vector>

#include "mediator/MediatorChannel.h"
#include "mediator/messages/requests/mediator_request_headers.h"
#include "mediator/messages/responses/mediator_response_headers.h"

/**
 * This communicator is responsible to send request and receive responses
 * from the main channel of the mediator.
 */
class MediatorMainCommunicator
{
private:
    MediatorChannel m_channel;
    std::string m_currentTripName;
    
public:
    MediatorMainCommunicator(std::string host, uint16_t port);
    ~MediatorMainCommunicator();

    // ==== RECORD ====
    std::unique_ptr<TrSave_MediatorResponse> startRecord();
    void registerData(std::unique_ptr<TrRegister_MediatorRequest> registerRequest, std::vector<unsigned char>& imageData);
    std::unique_ptr<TrEndSave_MediatorResponse> endRecord();

    // ==== PATH ====
    std::unique_ptr<PathList_MediatorResponse> fetchPathList();
    std::unique_ptr<PathOne_MediatorResponse> fetchOnePath(long pathId);

    void launchPath(long pathId);

    // ==== ERROR ====
    void startErrorMode();
    void endErrorMode();
};

#endif // __MEDIATORMAINCOMMUNICATOR_H__