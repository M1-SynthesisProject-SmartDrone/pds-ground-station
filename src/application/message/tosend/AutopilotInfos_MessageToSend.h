#ifndef __AUTOPILOTINFOS_MESSAGETOSEND_H__
#define __AUTOPILOTINFOS_MESSAGETOSEND_H__

#include "Abstract_ApplicationToSendMessage.h"

/**
 * A message sent periodically to the app in order to update drone infos on the UI.
 * @author Aldric Vitali Silvestre
 */
struct AutopilotInfos_MessageToSend : Abstract_ApplicationToSendMessage
{
    bool isArmed;

    bool isRecording;

    /**
     * From 0% to 100%
     */
    int8_t batteryRemaining;

    /**
     * Gps coordinates lat, lon (degE7)
     */
    int32_t lat;
    int32_t lon;

    /**
     * Altitude above sea level (mm)
     */
    int32_t alt;

    /**
     * Altitude above ground (mm)
     */
    int32_t relativeAlt;

    /**
     * Ground spped (cm/s)
     */ 
    int16_t vx;
    int16_t vy;
    int16_t vz;

    /**
     * Drone rotation (cdeg)
     * Angle arround z-axis (from top to bottom), a.k.a "yaw"
     */ 
    uint16_t yawRotation;

    bool running;

    bool errorMode;

    bool manualControl;

    AutopilotInfos_MessageToSend()
    {
        this->messageType = MESSAGE_TYPE::RESP_AUTOPILOT_INFOS;
    }

    std::string getMessageType()
    {
        return "RESP_AUTOPILOT_INFOS";
    }

    nlohmann::json createContent()
    {
        return {
            {"armed", this->isArmed},
            {"recording", this->isRecording},
            {"batteryRemaining", this->batteryRemaining},
            {"lat", this->lat},
            {"lon", this->lon},
            {"alt", this->alt},
            {"relativeAlt", this->relativeAlt},
            {"vx", this->vx},
            {"vy", this->vy},
            {"vz", this->vz},
            {"yawRotation", this->yawRotation},
            {"running", this->running},
            {"errorMode", this->errorMode},
            {"manualControl", this->manualControl}
        };
    }
};

#endif // __AUTOPILOTINFOS_MESSAGETOSEND_H__