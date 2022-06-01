#ifndef __PATHONE_MESSAGERECEIVED_H__
#define __PATHONE_MESSAGERECEIVED_H__

#include "./Abstract_ApplicationReceivedMessage.h"

/**
 * @author Aldric Vitali Silvestre
 */
struct PathOne_MessageReceived : Abstract_ApplicationReceivedMessage
{
    long pathId;

    PathOne_MessageReceived(long pathId)
    {
        this->pathId = pathId;
        this->messageType = MESSAGE_TYPE::REQ_PATH_ONE;
    }

    std::string toString()
    {
        std::stringstream ss;
        ss << "PathOne_MessageReceived [pathId=" << this->pathId << "]";
        return ss.str();
    }
};
#endif // __PATHONE_MESSAGERECEIVED_H__