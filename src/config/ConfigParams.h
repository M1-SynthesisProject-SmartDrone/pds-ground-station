#ifndef __CONFIGPARAMS_H__
#define __CONFIGPARAMS_H__

struct ConfigGlobal
{
    std::string tmpFolderPath;
};

struct ConfigApp
{
    // No need for host, as we will respond to it directly
    int sendPort;
    int receivePort;
};

struct ConfigMediator
{
    std::string host;
    int mainSendPort;
    int mainReceivePort;
    int secondarySendPort;
    int secondaryReceivePort;
};

/**
 * The struct containing all config params
 */
struct ConfigParams
{
    ConfigGlobal globalParams;
    ConfigApp appParams;
    ConfigMediator mediatorParams;

    ConfigParams(ConfigGlobal global, ConfigApp app, ConfigMediator mediator)
    {
        this->globalParams = global;
        this->appParams = app;
        this->mediatorParams = mediator;
    }
};

#endif // __CONFIGPARAMS_H__