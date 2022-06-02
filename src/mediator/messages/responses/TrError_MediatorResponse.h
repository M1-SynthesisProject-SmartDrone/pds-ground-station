#ifndef __TRERROR_MEDIATORRESPONSE_H__
#define __TRERROR_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct TrError_MediatorResponse : Abstract_MediatorResponse
{
    TrError_MediatorResponse()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_ERROR;
    }

    std::string toString()
    {
        return "TRError_MediatorResponse";
    }
};

#endif // __TRERROR_MEDIATORRESPONSE_H__