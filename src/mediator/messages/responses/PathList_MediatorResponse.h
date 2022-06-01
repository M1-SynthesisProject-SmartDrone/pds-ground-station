#ifndef __PATHLIST_MEDIATORRESPONSE_H__
#define __PATHLIST_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

#include <vector>

struct RespPathList_Item
{
    std::string name;
    long id;
    time_t timestamp;
};

struct PathList_MediatorResponse : Abstract_MediatorResponse
{
    std::vector<RespPathList_Item> paths;

    PathList_MediatorResponse()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_PATH_LIST;
    }

    std::string toString()
    {
        return "PathList_MediatorResponse";
    }
};
#endif // __PATHLIST_MEDIATORRESPONSE_H__