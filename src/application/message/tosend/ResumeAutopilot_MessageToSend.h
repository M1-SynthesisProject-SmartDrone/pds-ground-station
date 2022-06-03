#ifndef __RESUMEAUTOPILOT_MESSAGETOSEND_H__
#define __RESUMEAUTOPILOT_MESSAGETOSEND_H__

#include "Abstract_Answer_MessageToSend.h"

struct ResumeAutopilot_MessageToSend : Abstract_Answer_MessageToSend
{
    ResumeAutopilot_MessageToSend(bool validated, std::string message = "")
    : Abstract_Answer_MessageToSend(MESSAGE_TYPE::RESP_ACK, validated, message)
    {}

    std::string getMessageType()
    {
        return "RESP_RESUME_AUTOPILOT";
    }
};

#endif // __RESUMEAUTOPILOT_MESSAGETOSEND_H__