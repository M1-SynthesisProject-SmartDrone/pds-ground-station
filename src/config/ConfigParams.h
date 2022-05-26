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

struct ConfigPathRegister
{
    int saveFrequency;
    int savesBetweenCheckpoints;
};

struct ConfigMediator
{
    std::string host;
    int mainPort;
    int secondaryPort;
};

/**
 * The struct containing all config params
 */
struct ConfigParams
{
    ConfigGlobal global;
    ConfigApp app;
    ConfigMediator mediator;
    ConfigPathRegister pathRegister;

    ConfigParams(ConfigGlobal global, ConfigApp app, ConfigMediator mediator, ConfigPathRegister pathRegister)
    {
        this->global = global;
        this->app = app;
        this->mediator = mediator;
        this->pathRegister = pathRegister;
    }
};

#endif // __CONFIGPARAMS_H__