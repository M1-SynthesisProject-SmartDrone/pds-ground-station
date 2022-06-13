#ifndef __TRENDLAUNCH_MEDIATORREQUEST_H__
#define __TRENDLAUNCH_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct TrEndLaunch_MediatorRequest : Abstract_MediatorRequest
{
    TrEndLaunch_MediatorRequest()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_TR_END_LAUNCH;
    }

    std::string toString()
    {
        return "TrEndLaunch_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("END_TR_LAUNCH");
        return document.dump();
    }
};

#endif // __TRENDLAUNCH_MEDIATORREQUEST_H__