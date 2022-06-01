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

    std::string getMessageType()
    {
        return "RESP_PATH_ONE";
    }

    nlohmann::json createContent()
    {
        return {
        {"id", this->id},
        {"name", this->name},
        {"date", this->date},
        {"nbPoints", this->nbPoints},
        {"nbCheckpoints", this->nbCheckpoints},
        {"departure", {
            {"lat", this->departureLat},
            {"lon", this->departureLon},
            {"alt", this->departureAlt},
        }}
    };
    }
};

#endif // __PATHONE_MESSAGETOSEND_H__