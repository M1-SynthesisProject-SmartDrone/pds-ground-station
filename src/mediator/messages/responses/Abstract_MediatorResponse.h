#ifndef __ABSTRACT_MEDIATORRESPONSE_H__
#define __ABSTRACT_MEDIATORRESPONSE_H__

#include "mediator/messages/Abstract_MediatorMessage.h"

struct Abstract_MediatorResponse : Abstract_MediatorMessage
{
    virtual std::string toString()
    {
        return "Abstract_MediatorResponse";
    }


};

#endif // __ABSTRACT_MEDIATORRESPONSE_H__