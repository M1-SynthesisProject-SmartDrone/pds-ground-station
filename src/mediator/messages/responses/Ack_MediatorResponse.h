#ifndef __ACK_MEDIATORRESPONSE_H__
#define __ACK_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct Ack_MediatorResponse : Abstract_MediatorResponse
{
    bool valid;

    Ack_MediatorResponse(bool valid = true)
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_ACK;
        this->valid = valid;
    }

    std::string toString()
    {
        return "Ack_MediatorResponse [valid: " + std::to_string(valid) + "]";
    }
};

#endif // __ACK_MEDIATORRESPONSE_H__