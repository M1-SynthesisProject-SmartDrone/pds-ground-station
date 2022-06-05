#ifndef __TRREGISTER_MEDIATORRESPONSE_H__
#define __TRREGISTER_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrRegister_MediatorResponse : Abstract_MediatorResponse
{
    bool isDone;

    TrRegister_MediatorResponse(bool isDone)
    {
        this->isDone = isDone;
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_REGISTER;
    }

    std::string toString()
    {
        std::stringstream ss;
        ss << "TrRegister_MediatorResponse [isDone=" << this->isDone << "]";
        return ss.str();
    }
};

#endif // __TRREGISTER_MEDIATORRESPONSE_H__