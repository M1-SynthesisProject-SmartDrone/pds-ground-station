#ifndef __PATHLIST_MESSAGETOSEND_H__
#define __PATHLIST_MESSAGETOSEND_H__

#include "Abstract_ApplicationToSendMessage.h"

#include <vector>

struct PathList_Path
{
    std::string name;
    long id;
    std::string date;
};

/**
 * @author Aldric Vitali Silvestre
 */
struct PathList_MessageToSend : Abstract_ApplicationToSendMessage
{
    std::vector<PathList_Path> paths;

    PathList_MessageToSend()
    {
        this->messageType = MESSAGE_TYPE::RESP_PATH_LIST;
    }
};

#endif // __PATHLIST_MESSAGETOSEND_H__