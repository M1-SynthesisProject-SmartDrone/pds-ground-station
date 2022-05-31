#ifndef __PATHONE_MESSAGETOSEND_H__
#define __PATHONE_MESSAGETOSEND_H__


#include "Abstract_ApplicationToSendMessage.h"

/**
 * @author Aldric Vitali Silvestre
 */
struct PathOne_MessageToSend : Abstract_ApplicationToSendMessage
{
    long id;
    std::string name;
    std::string date;
    int nbPoints;
    int nbCheckpoints;
    std::string departureLat;
    std::string departureLon;
    std::string departureAlt;

    PathOne_MessageToSend()
    {
        this->messageType = MESSAGE_TYPE::RESP_PATH_ONE;
    }
};

#endif // __PATHONE_MESSAGETOSEND_H__