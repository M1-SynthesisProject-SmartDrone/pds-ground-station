#ifndef __ABSTRACT_MEDIATORMESSAGE_H__
#define __ABSTRACT_MEDIATORMESSAGE_H__

#include <string>
#include "MediatorMessageType.h"

/**
 * All messages related to mediator inherit this struct
 */
struct Abstract_MediatorMessage
{
    MEDIATOR_MESSAGE_TYPE messageType;

    virtual std::string toString() = 0;
};

#endif // __ABSTRACT_MEDIATORMESSAGE_H__