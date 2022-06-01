#ifndef __PATHLAUNCH_MESSAGETOSEND_H__
#define __PATHLAUNCH_MESSAGETOSEND_H__

#include "Abstract_Answer_MessageToSend.h"

struct PathLaunch_MessageToSend : Abstract_Answer_MessageToSend
{
    PathLaunch_MessageToSend(bool validated, std::string message = "")
    : Abstract_Answer_MessageToSend(MESSAGE_TYPE::RESP_PATH_LAUNCH, validated, message)
    {}

    std::string getMessageType()
    {
        return "RESP_PATH_LAUNCH";
    }
};

#endif // __PATHLAUNCH_MESSAGETOSEND_H__