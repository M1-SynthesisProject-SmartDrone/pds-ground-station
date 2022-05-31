#ifndef __PATHLIST_MESSAGERECEIVED_H__
#define __PATHLIST_MESSAGERECEIVED_H__

#include "./Abstract_ApplicationReceivedMessage.h"

/**
 * @author Aldric Vitali Silvestre
 */
struct PathList_MessageReceived : Abstract_ApplicationReceivedMessage
{
    PathList_MessageReceived()
    {
        this->messageType = MESSAGE_TYPE::REQ_PATH_LIST;
    }

    std::string toString()
    {
        return "PathList_MessageReceived";
    }
};
#endif // __PATHLIST_MESSAGERECEIVED_H__