#include "ConfigParser.h"

#include <libconfig.h++>

using namespace std;
namespace fs = std::filesystem;

string getConfigPath(char* argv[])
{
    std::filesystem::path exePath(argv[0]);
    std::filesystem::path exeDirectoryPath = exePath.parent_path();
    return exeDirectoryPath.string() + "/config.cfg";
}

ConfigParser::ConfigParser(int argc, char* argv[])
{
    // The file must be aside the executable normally (done at cmake step)
    // If there is an issue, we must stop the app anyways, so let the exception throw
    string filename = getConfigPath(argv);
    m_confFilePath = fs::path(filename);
    if (!fs::exists(m_confFilePath))
    {
        throw runtime_error("Config file not found: " + filename);
    }
}

ConfigParser::~ConfigParser() {}

ConfigParams ConfigParser::parse()
{
    libconfig::Config config;

    config.readFile(m_confFilePath.c_str());

    const auto& root = config.getRoot();
    auto globalConfig = ConfigGlobal{
        root.lookup("tmp_folder")
    };

    const auto& appSettings = root["app"];
    auto appConfig = ConfigApp{
        appSettings["send_port"],
        appSettings["receive_port"]
    };

    const auto& mediatorSettings = root["mediator"];
    auto mediatorConfig = ConfigMediator{
        mediatorSettings["host"],
        mediatorSettings["main"]["send_port"],
        mediatorSettings["main"]["receive_port"],
        mediatorSettings["secondary"]["send_port"],
        mediatorSettings["secondary"]["receive_port"]
    };

    const auto& pathRegisterParams = root["path_register"];
    auto pathRegisterConfig = ConfigPathRegister{
        pathRegisterParams["save_frequency"],
        pathRegisterParams["saves_between_checkpoints"]
    };

    return ConfigParams(
        globalConfig,
        appConfig,
        mediatorConfig,
        pathRegisterConfig
    );
}

