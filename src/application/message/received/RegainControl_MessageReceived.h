#ifndef __REGAINCONTROL_MESSAGERECEIVED_H__
#define __REGAINCONTROL_MESSAGERECEIVED_H__

#include "./Abstract_ApplicationReceivedMessage.h"

/**
 * @author Aldric Vitali Silvestre
 */
struct RegainControl_MessageReceived : Abstract_ApplicationReceivedMessage
{
    RegainControl_MessageReceived()
    {
        this->messageType = MESSAGE_TYPE::REQ_REGAIN_CONTROL;
    }

    std::string toString()
    {
        return "RegainControl_MessageReceived";
    }
};

#endif // __REGAINCONTROL_MESSAGERECEIVED_H__