#ifndef __ANSWER_MESSAGETOSEND_H__
#define __ANSWER_MESSAGETOSEND_H__

#include "Abstract_ApplicationToSendMessage.h"

/**
 * This is another abstract class to simplify writing simple validation messages
 */
struct Abstract_Answer_MessageToSend : Abstract_ApplicationToSendMessage
{
    bool validated;
    std::string message;

    Abstract_Answer_MessageToSend(MESSAGE_TYPE messageType, bool validated, std::string message="")
    {
        this->messageType = messageType;
        this->validated = validated;
        this->message = message;
    }

    std::string toString()
    {
        std::stringstream ss;
        ss << "Answer_MessageToSend [type=" << (int)messageType << " validated = " << validated << "]";
        return ss.str();
    }
    
    virtual std::string getMessageType() = 0;

    nlohmann::json createContent() 
    {
        return {
            {"validated", this->validated},
            {"message", this->message},
        };
    }
};


#endif // __ANSWER_MESSAGETOSEND_H__