#ifndef __MEDIATORMAINCOMMUNICATOR_H__
#define __MEDIATORMAINCOMMUNICATOR_H__


#include <string>

/**
 * This communicator is responsible to send request and receive responses
 * from the main channel of the mediator.
 */
class MediatorMainCommunicator
{
private:
    
public:
    MediatorMainCommunicator(std::string host, uint16_t listenPort, uint16_t sendPort);
    ~MediatorMainCommunicator();

    void startRecord();
    
    void endRecord();
};

#endif // __MEDIATORMAINCOMMUNICATOR_H__