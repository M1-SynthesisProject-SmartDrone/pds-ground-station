#ifndef __TRREGISTER_MEDIATORREQUEST_H__
#define __TRREGISTER_MEDIATORREQUEST_H__

#include "Abstract_MediatorRequest.h"

struct TrRegister_MediatorRequest : Abstract_MediatorRequest
{
    int altitude;
    int latitude;
    int longitude;
    int rotation;
    float temperature;
    float pressure;
    int batteryRemaining;
    bool isCheckpoint;
    std::time_t time;
    std::string image;

    TrRegister_MediatorRequest()
    {
        this->messageType = MEDIATOR_MESSAGE_TYPE::REQ_REGISTER;
    }

    std::string toString()
    {
        return "TrRegister_MediatorRequest";
    }

    std::string toJson()
    {
        auto document = createBaseDocument("TR_REGISTER");
        document["altitude"] = altitude;
        document["latitude"] = latitude;
        document["longitude"] = longitude;
        document["rotation"] = rotation;
        document["temperature"] = temperature;
        document["pressure"] = pressure;
        document["batteryRemaining"] = batteryRemaining;
        document["isCheckpoint"] = isCheckpoint;
        document["time"] = time;
        document["image"] = image;
        return document.dump();
    }
};

#endif // __TRREGISTER_MEDIATORREQUEST_H__