#ifndef __JSON_RECIVEDMESSAGESCONVERTER_H__
#define __JSON_RECIVEDMESSAGESCONVERTER_H__

#include <string>
#include <unordered_map>
#include <functional>

#include <nlohmann/json.hpp>

#include "application/message/received/recevied_headers.h"

class Json_ReceivedMessagesConverter
{
private:
    Ack_MessageReceived* parseAckRequest(nlohmann::json& obj);
    Start_MessageReceived* parseStartRequest(nlohmann::json& obj);
    Record_MessageReceived* parseRecordRequest(nlohmann::json& obj);
    Manual_MessageReceived* parseManualRequest(nlohmann::json& obj);
    DroneInfos_MessageReceived* parseDroneInfosRequest(nlohmann::json& obj);
    PathList_MessageReceived* parsePathListRequest(nlohmann::json& obj);
    PathOne_MessageReceived* parsePathOneRequest(nlohmann::json& obj);
    PathLaunch_MessageReceived* parsePathLaunchRequest(nlohmann::json& obj);
    AutopilotInfos_MessageReceived* parseAutopilotInfosRequest(nlohmann::json& obj);
    RegainControl_MessageReceived* parseRegainControlRequest(nlohmann::json& obj);
    ResumeAutopilot_MessageReceived* parseResumeAutopilotRequest(nlohmann::json& obj);

    std::function<Abstract_ApplicationReceivedMessage*(nlohmann::json&)> 
        findMessageConverterFunc(nlohmann::json& document);

    /**
     * This map contains method references (as lambdas) to converters for each message type (key are strings).
     * Contains only request messages, responses messages does not have to be parsed
     */
    const std::unordered_map<
        std::string,
        // This is a bit long, but it is better not to throw aliases in header files
        // And yes, lambdas are a bit ugly in c++, but safier than raw function pointers (and std::bind)
        std::function<Abstract_ApplicationReceivedMessage*(nlohmann::json&)>
        > CONVERTER_FROM_STR {
        {"ACK", [this](auto content) {return parseAckRequest(content);}},
        {"START_DRONE", [this](auto content) {return parseStartRequest(content);}},
        {"MANUAL_CONTROL", [this](auto content) {return parseManualRequest(content);}},
        {"RECORD", [this](auto content) {return parseRecordRequest(content);}},
        {"DRONE_INFOS", [this](auto content) {return parseDroneInfosRequest(content);}},
        {"PATH_LIST", [this](auto content) {return parsePathListRequest(content);}},
        {"PATH_ONE", [this](auto content) {return parsePathOneRequest(content);}},
        {"PATH_LAUNCH", [this](auto content) {return parsePathLaunchRequest(content);}},
        {"AUTOPILOT_INFOS", [this](auto content) {return parseAutopilotInfosRequest(content);}},
        {"REGAIN_CONTROL", [this](auto content) {return parseRegainControlRequest(content);}},
        {"RESUME_AUTOPILOT", [this](auto content) {return parseResumeAutopilotRequest(content);}},
    };
public:
    Json_ReceivedMessagesConverter();
    ~Json_ReceivedMessagesConverter();

    Abstract_ApplicationReceivedMessage* convertMessageReceived(std::string message);
};

#endif // __JSON_RECIVEDMESSAGESCONVERTER_H__