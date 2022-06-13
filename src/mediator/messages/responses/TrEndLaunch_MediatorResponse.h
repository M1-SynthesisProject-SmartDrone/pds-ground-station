#ifndef __TRENDLAUNCH_MEDIATORRESPONSE_H__
#define __TRENDLAUNCH_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrEndLaunch_MediatorResponse : Abstract_MediatorResponse
{
    TrEndLaunch_MediatorResponse()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_END_LAUNCH;
    }

    std::string toString()
    {
        return "TrEndLaunch_MediatorResponse";
    }
};

#endif // __TRENDLAUNCH_MEDIATORRESPONSE_H__