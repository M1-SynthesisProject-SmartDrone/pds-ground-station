#ifndef __ABSTRACT_ANDROIDTOSENDMESSAGE_H__
#define __ABSTRACT_ANDROIDTOSENDMESSAGE_H__

#include <nlohmann/json.hpp>

#include "application/message/Abstract_ApplicationMessage.h"

struct Abstract_ApplicationToSendMessage : Abstract_ApplicationMessage
{
    virtual std::string toString()
    {
        return "Abstract_ApplicationToSendMessage";
    }

    std::string toJson()
    {
        nlohmann::json document;
        document["type"] = getMessageType();
        document["content"] = createContent();
        return document.dump();
    };

    virtual std::string getMessageType() = 0;

    virtual nlohmann::json createContent() = 0;
};

#endif // __ABSTRACT_ANDROIDTOSENDMESSAGE_H__