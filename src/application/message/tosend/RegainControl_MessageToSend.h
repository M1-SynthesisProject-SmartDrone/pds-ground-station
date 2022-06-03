#ifndef __REGAINCONTROL_MESSAGETOSEND_H__
#define __REGAINCONTROL_MESSAGETOSEND_H__

#include "Abstract_Answer_MessageToSend.h"

struct RegainControl_MessageToSend : Abstract_Answer_MessageToSend
{
    RegainControl_MessageToSend(bool validated, std::string message = "")
    : Abstract_Answer_MessageToSend(MESSAGE_TYPE::RESP_ACK, validated, message)
    {}

    std::string getMessageType()
    {
        return "RESP_REGAIN_CONTROL";
    }
};

#endif // __REGAINCONTROL_MESSAGETOSEND_H__