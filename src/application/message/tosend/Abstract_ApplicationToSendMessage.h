#ifndef __ABSTRACT_ANDROIDTOSENDMESSAGE_H__
#define __ABSTRACT_ANDROIDTOSENDMESSAGE_H__

#include "application/message/Abstract_ApplicationMessage.h"

struct Abstract_ApplicationToSendMessage : Abstract_ApplicationMessage
{
    virtual std::string toString()
    {
        return "Abstract_ApplicationToSendMessage";
    }
};

#endif // __ABSTRACT_ANDROIDTOSENDMESSAGE_H__