#ifndef __ABSTRACT_MEDIATORREQUEST_H__
#define __ABSTRACT_MEDIATORREQUEST_H__

#include <nlohmann/json.hpp>

#include "mediator/messages/Abstract_MediatorMessage.h"

struct Abstract_MediatorRequest : Abstract_MediatorMessage
{
    virtual std::string toString()
    {
        return "Abstract_MediatorRequest";
    }

    nlohmann::json createBaseDocument(const char* messageType)
    {
        nlohmann::json document;
        document["requestType"] = messageType;
        return document;
    }

    virtual std::string toJson() = 0;
};


#endif // __ABSTRACT_MEDIATORREQUEST_H__