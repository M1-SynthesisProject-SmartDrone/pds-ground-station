#ifndef __TRERROR_MEDIATORREQUEST_H__
#define __TRERROR_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct TrError_MediatorRequest : Abstract_MediatorRequest
{
    TrError_MediatorRequest()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_PATH_LIST;
    }

    std::string toString()
    {
        return "TrError_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("TR_ERROR");
        return document.dump();
    }
};

#endif // __TRERROR_MEDIATORREQUEST_H__