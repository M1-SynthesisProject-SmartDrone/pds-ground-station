#ifndef __TRSAVE_MEDIATORREQUEST_H__
#define __TRSAVE_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct TrSave_MediatorRequest : Abstract_MediatorRequest
{

    TrSave_MediatorRequest()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_TR_SAVE;
    }

    std::string toString()
    {
        return "TRSave_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("TR_SAVE");
        return document.dump();
    }
};


#endif // __TRSAVE_MEDIATORREQUEST_H__