#ifndef __ABSTRACT_ANDROIDMESSAGECONVERTER_H__
#define __ABSTRACT_ANDROIDMESSAGECONVERTER_H__
/**
 * Abstract helper class to convert messages received.
 * This class is declared inline as no real logic happens here. 
 * 
 * @author Aldric Vitali Silvestre
 */

#include "application/message/received/Abstract_ApplicationReceivedMessage.h"
#include "application/message/tosend/Abstract_ApplicationToSendMessage.h"
#include <string>

class Abstract_ApplicationMessageConverter
{
public:
    virtual Abstract_ApplicationReceivedMessage* convertMessageReceived(std::string message) = 0;
    
    virtual std::string convertToSendMessage(Abstract_ApplicationToSendMessage* message) = 0;
    
private:

};

#endif // __ABSTRACT_ANDROIDMESSAGECONVERTER_H__