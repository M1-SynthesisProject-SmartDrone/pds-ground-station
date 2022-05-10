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

/**
 * The struct containing all config params
 */
struct ConfigParams
{
    ConfigGlobal globalParams;
    ConfigApp appParams;

    ConfigParams(ConfigGlobal global, ConfigApp app)
    {
        this->globalParams = global;
        this->appParams = app;
    }
};

#endif // __CONFIGPARAMS_H__