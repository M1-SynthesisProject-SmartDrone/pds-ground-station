#ifndef __PATHLIST_MEDIATORREQUEST_H__
#define __PATHLIST_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct PathList_MediatorRequest : Abstract_MediatorRequest
{
    PathList_MediatorRequest()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_PATH_LIST;
    }

    std::string toString()
    {
        return "PathList_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("GET_PATH_LIST");
        return document.dump();
    }
};

#endif // __PATHLIST_MEDIATORREQUEST_H__