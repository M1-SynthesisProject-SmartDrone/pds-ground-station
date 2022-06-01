#ifndef __TRLAUNCH_MEDIATORRESPONSE_H__
#define __TRLAUNCH_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrLaunch_MediatorResponse : Abstract_MediatorResponse
{
    long isDone;

    TrLaunch_MediatorResponse(bool isDone)
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_LAUNCH;
        this->isDone = isDone;
    }

    std::string toString()
    {
        return "TrLaunch_MediatorResponse";
    }
};

#endif // __TRLAUNCH_MEDIATORRESPONSE_H__