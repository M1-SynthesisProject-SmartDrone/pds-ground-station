#ifndef __TRREGISTER_MEDIATORRESPONSE_H__
#define __TRREGISTER_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrRegister_MediatorResponse : Abstract_MediatorResponse
{
    bool isDone;

    TrRegister_MediatorResponse(bool isDone)
    {
        this->isDone;
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_REGISTER;
    }

    std::string toString()
    {
        return "TrRegister_MediatorResponse";
    }
};

#endif // __TRREGISTER_MEDIATORRESPONSE_H__