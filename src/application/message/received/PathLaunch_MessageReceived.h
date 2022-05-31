#ifndef __PATHLAUNCH_MESSAGERECEIVED_H__
#define __PATHLAUNCH_MESSAGERECEIVED_H__

#include "./Abstract_ApplicationReceivedMessage.h"

/**
 * @author Aldric Vitali Silvestre
 */
struct PathLaunch_MessageReceived : Abstract_ApplicationReceivedMessage
{
    long pathId;

    PathLaunch_MessageReceived(long pathId)
    {
        this->pathId = pathId;
        this->messageType = MESSAGE_TYPE::REQ_PATH_ONE;
    }

    std::string toString()
    {
        stringstream ss;
        ss << "PathLaunch_MessageReceived [pathId=" << this->pathId << "]";
        return ss.str();
    }
};
#endif // __PATHLAUNCH_MESSAGERECEIVED_H__