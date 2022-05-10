#ifndef __ABSTRACT_ANDROIDRECEIVEDMESSAGE_H__
#define __ABSTRACT_ANDROIDRECEIVEDMESSAGE_H__

#include "application/message/Abstract_ApplicationMessage.h"

/**
 * All messages received from the application application will inherit this structure
 */
struct Abstract_ApplicationReceivedMessage : Abstract_ApplicationMessage
{

    virtual std::string toString()
    {
        return "Abstract_ApplicationReceivedMessage";
    }
};

#endif // __ABSTRACT_ANDROIDRECEIVEDMESSAGE_H__