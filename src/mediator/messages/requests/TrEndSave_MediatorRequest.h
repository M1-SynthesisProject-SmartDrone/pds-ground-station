#ifndef __TRENDSAVE_MEDIATORREQUEST_H__
#define __TRENDSAVE_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct TrEndSave_MediatorRequest : Abstract_MediatorRequest
{
    std::string tripName;

    TrEndSave_MediatorRequest(std::string tripName)
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_END_TR_SAVE;
        this->tripName = tripName;
    }

    std::string toString()
    {
        return "TrEndSave_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("END_TR_SAVE");
        document["tripName"] = tripName;
        return document.dump();
    }
};

#endif // __TRENDSAVE_MEDIATORREQUEST_H__