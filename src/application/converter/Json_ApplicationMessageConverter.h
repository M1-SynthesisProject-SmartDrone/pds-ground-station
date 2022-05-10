#ifndef __JSON_ANDROIDMESSAGECONVERTER_H__
#define __JSON_ANDROIDMESSAGECONVERTER_H__

/**
 * An implementation of the Abstract_ApplicationMessageConverter class
 * that can convert JSON formatted strings
 *
 * @author Aldric Vitali Silvestre
 */
 // Library used : https://rapidjson.org/

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <string>

#include "Abstract_ApplicationMessageConverter.h"

#include "application/message/tosend/Abstract_ApplicationToSendMessage.h"
#include "application/message/received/Abstract_ApplicationReceivedMessage.h"

#include "application/converter/Json_ReceivedMessagesConverter.h"
#include "application/converter/Json_ToSendMessagesConverter.h"

class Json_ApplicationMessageConverter : public Abstract_ApplicationMessageConverter
{
public:
    Json_ApplicationMessageConverter();
    ~Json_ApplicationMessageConverter();

    Abstract_ApplicationReceivedMessage* convertMessageReceived(std::string message);
    std::string convertToSendMessage(Abstract_ApplicationToSendMessage* message);
private:
    std::unique_ptr<Json_ReceivedMessagesConverter> m_receivedMessagesConverter;
    std::unique_ptr<Json_ToSendMessagesConverter> m_toSendMessagesConverter;
};


#endif // __JSON_ANDROIDMESSAGECONVERTER_H__