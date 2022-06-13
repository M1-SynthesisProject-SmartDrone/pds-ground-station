#include <iostream>
#include <errno.h>
#include <thread>
#include <vector>
#include <random>
#include <stdexcept>
#include <filesystem>
#include <stdlib.h>
#include <sstream>
#include <unistd.h>
#include <signal.h>

#include <loguru/loguru.hpp>
#include <opencv2/opencv.hpp>

#include "config/ConfigParser.h"
#include "ground_station/GroundStation.h"
#include "application/network/ApplicationMediator.h"
#include "application/converter/Json_ApplicationMessageConverter.h"
#include "drone/DroneCommunicator.h"
#include "mediator/MediatorMainCommunicator.h"
#include "mediator/MediatorSecondaryCommunicator.h"

#include "channels/channels.h"

using namespace std;

void initSignalHandler();
void signalHandler(int number);
void handleExit();

unique_ptr<GroundStation> groundStation = nullptr;

/**
 * THIS APPLICATION MUST BE LAUNCHED AFTER THE DRONE INTERFACE ONE
 * (or another program that opens the channels)
 */
int main(int argc, char* argv[])
{
    loguru::init(argc, argv);
    LOG_F(INFO, "Start the 'Ground Station' application");

    initSignalHandler();

    ConfigParser configParser(argc, argv);
    ConfigParams params = configParser.parse();

    auto androidMediator = make_shared<ApplicationMediator>(
        params.app.receivePort,
        params.app.sendPort,
        make_unique<Json_ApplicationMessageConverter>()
    );

    auto mediatorMainCommunicator = make_shared<MediatorMainCommunicator>(
        params.mediator.host,
        params.mediator.mainPort
    );
    usleep(1000 * 1000);
    auto mediatorSecondaryCommunicator = make_shared<MediatorSecondaryCommunicator>(
        params.mediator.host,
        params.mediator.secondaryPort
    );
    auto droneCommunicator = make_shared<DroneCommunicator>();
    groundStation = make_unique<GroundStation>(
        params,
        androidMediator,
        mediatorMainCommunicator,
        mediatorSecondaryCommunicator,
        droneCommunicator
    );
    
    groundStation->run();

    // ==== Test for getting and displaying the image in blc_channels ====
    // auto imgBuffer = pdsChannels::image.uchars;
    // auto rows = pdsChannels::imageSize.uints32[0];
    // auto cols = pdsChannels::imageSize.uints32[1];
    // auto imgSize = pdsChannels::imageSize.uints32[2];

    // string encoded = encode_base64(imgBuffer, imgSize);
    // string decoded = decode_base64(encoded);

    // cv::Mat img(rows, cols, CV_8UC3, decoded.data());
    // cout << img.cols << " == " << img.rows << "\n";

    // cv::imshow("fenetre", img);
    // cv::waitKey(0);

    LOG_F(INFO, "End of ground station server");
    return EXIT_SUCCESS;
}

void initSignalHandler()
{
    LOG_F(INFO, "Init signal handler");
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);
    signal(SIGTERM, signalHandler);
    signal(SIGFPE, signalHandler);
}

void signalHandler(int number)
{
    int exitStatus = 0;
    switch (number)
    {
    case SIGINT:
        LOG_F(WARNING, "SIGINT caught");
        handleExit();
        exit(0);
        break;
    case SIGQUIT:
        LOG_F(WARNING, "SIGQUIT caught");
        handleExit();
        exit(0);
        break;
    case SIGTERM:
        LOG_F(WARNING, "SIGTERM caught");
        handleExit();
        exit(1);
        break;
    case SIGFPE:
        LOG_F(WARNING, "SIGFPE caught");
        handleExit();
        exit(2);
        break;
    default:
        LOG_F(WARNING, "Unhandled signal caught : %d", number);
        break;
    }
}

void handleExit()
{
    // Close opened channels here

    if (groundStation)
    {
        groundStation->askStopRunning();
    }
}