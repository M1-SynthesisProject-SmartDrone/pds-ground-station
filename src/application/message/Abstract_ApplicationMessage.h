#ifndef __ABSTRACT_ANDROIDMESSAGE_H__
#define __ABSTRACT_ANDROIDMESSAGE_H__

#include <iostream>
#include "MessageType.h"

/**
 * All messages related to application inherit this struct
 */
struct Abstract_ApplicationMessage
{
    MESSAGE_TYPE messageType;

    virtual std::string toString() = 0;
};

#endif // __ABSTRACT_ANDROIDMESSAGE_H__