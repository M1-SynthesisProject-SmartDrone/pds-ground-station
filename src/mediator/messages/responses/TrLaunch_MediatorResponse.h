#ifndef __TRLAUNCH_MEDIATORRESPONSE_H__
#define __TRLAUNCH_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrLaunch_MediatorResponse : Abstract_MediatorResponse
{
    long id;

    TrLaunch_MediatorResponse(long id)
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_LAUNCH;
        this->id = id;
    }

    std::string toString()
    {
        return "TrLaunch_MediatorResponse [id: " + std::to_string(id) + "]";
    }
};

#endif // __TRLAUNCH_MEDIATORRESPONSE_H__