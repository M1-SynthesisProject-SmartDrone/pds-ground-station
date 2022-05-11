#ifndef __ABSTRACT_MEDIATORREQUEST_H__
#define __ABSTRACT_MEDIATORREQUEST_H__

#include "mediator/messages/Abstract_MediatorMessage.h"

struct Abstract_MediatorRequest : Abstract_MediatorMessage
{
    virtual std::string toString()
    {
        return "Abstract_MediatorRequest";
    }

    virtual std::string toJson() = 0;
};


#endif // __ABSTRACT_MEDIATORREQUEST_H__