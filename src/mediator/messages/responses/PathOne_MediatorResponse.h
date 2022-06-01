#ifndef __PATHONE_MEDIATORRESPONSE_H__
#define __PATHONE_MEDIATORRESPONSE_H__

#include "Abstract_MediatorResponse.h"

struct PathOne_MediatorResponse : Abstract_MediatorResponse
{
    std::string name;
    long id;
    int nbPoints;
    int nbCheckpoints;
    time_t date;
    int depLatitude;
    int depLongitude;
    int depAltitude;

    PathOne_MediatorResponse()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::RESP_PATH_ONE;
    }

    std::string toString()
    {
        return "PathOne_MediatorResponse";
    }
};

#endif // __PATHONE_MEDIATORRESPONSE_H__