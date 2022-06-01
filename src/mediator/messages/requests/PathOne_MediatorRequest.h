#ifndef __PATHONE_MEDIATORREQUEST_H__
#define __PATHONE_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct PathOne_MediatorRequest : Abstract_MediatorRequest
{
    long id;

    PathOne_MediatorRequest(long id)
    {
        this->id = id;
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_PATH_LIST;
    }

    std::string toString()
    {
        return "PathOne_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("GET_ONE_PATH");
        document["tr_id"] = this->id;
        return document.dump();
    }
};

#endif // __PATHONE_MEDIATORREQUEST_H__