#ifndef __PATHLAUNCH_MEDIATORREQUEST_H__
#define __PATHLAUNCH_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct TrLaunch_MediatorRequest : Abstract_MediatorRequest
{
    long id;

    TrLaunch_MediatorRequest(long id)
    {
        this->id = id;
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_TR_LAUNCH;
    }

    std::string toString()
    {
        return "TrLaunch_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("TR_LAUNCH");
        document["tr_id"] = this->id;
        return document.dump();
    }
};

#endif // __PATHLAUNCH_MEDIATORREQUEST_H__