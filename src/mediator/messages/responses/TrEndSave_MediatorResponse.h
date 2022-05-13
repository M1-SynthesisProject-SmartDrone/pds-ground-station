#ifndef __TRENDSAVE_MEDIATORRESPONSE_H__
#define __TRENDSAVE_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrEndSave_MediatorResponse : Abstract_MediatorResponse
{
    bool isLaunched;

    TrEndSave_MediatorResponse(bool isLaunched)
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_END_TR_SAVE;
        this->isLaunched = isLaunched;
    }

    std::string toString()
    {
        return "TrEndSave_MediatorResponse [isLaunched: " + std::to_string(isLaunched) + "]";
    }
};

#endif // __TRENDSAVE_MEDIATORRESPONSE_H__