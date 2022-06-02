#ifndef __TRENDERROR_MEDIATORREQUEST_H__
#define __TRENDERROR_MEDIATORREQUEST_H__


#include "Abstract_MediatorRequest.h"

struct TrEndError_MediatorRequest : Abstract_MediatorRequest
{
    TrEndError_MediatorRequest()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_TR_ERROR;
    }

    std::string toString()
    {
        return "TrEndError_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("END_TR_ERROR");
        return document.dump();
    }
};

#endif // __TRENDERROR_MEDIATORREQUEST_H__