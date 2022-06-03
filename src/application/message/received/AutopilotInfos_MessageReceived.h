#ifndef __AUTOPILOTINFOS_MESSAGERECEIVED_H__
#define __AUTOPILOTINFOS_MESSAGERECEIVED_H__

#include "./Abstract_ApplicationReceivedMessage.h"

/**
 * @author Aldric Vitali Silvestre
 */
struct AutopilotInfos_MessageReceived : Abstract_ApplicationReceivedMessage
{
    AutopilotInfos_MessageReceived()
    {
        this->messageType = MESSAGE_TYPE::REQ_AUTOPILOT_INFOS;
    }

    std::string toString()
    {
        return "AutopilotInfos_MessageReceived";
    }
};

#endif // __AUTOPILOTINFOS_MESSAGERECEIVED_H__