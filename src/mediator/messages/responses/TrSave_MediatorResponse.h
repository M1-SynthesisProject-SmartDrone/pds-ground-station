#ifndef __TRSAVE_MEDIATORRESPONSE_H__
#define __TRSAVE_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrSave_MediatorResponse : Abstract_MediatorResponse
{
    bool isLaunched;

    TrSave_MediatorResponse(bool isLaunched)
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_SAVE;
        this->isLaunched = isLaunched;
    }

    std::string toString()
    {
        return "TRSave_MediatorResponse [isLaunched: " + std::to_string(isLaunched) + "]";
    }
};


#endif // __TRSAVE_MEDIATORRESPONSE_H__