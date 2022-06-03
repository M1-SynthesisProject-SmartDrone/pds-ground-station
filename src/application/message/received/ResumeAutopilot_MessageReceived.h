#ifndef __RESUMEAUTOPILOT_MESSAGERECEIVED_H__
#define __RESUMEAUTOPILOT_MESSAGERECEIVED_H__

#include "./Abstract_ApplicationReceivedMessage.h"

/**
 * @author Aldric Vitali Silvestre
 */
struct ResumeAutopilot_MessageReceived : Abstract_ApplicationReceivedMessage
{
    ResumeAutopilot_MessageReceived()
    {
        this->messageType = MESSAGE_TYPE::REQ_RESUME_AUTOPILOT;
    }

    std::string toString()
    {
        return "ResumeAutopilot_MessageReceived";
    }
};

#endif // __RESUMEAUTOPILOT_MESSAGERECEIVED_H__