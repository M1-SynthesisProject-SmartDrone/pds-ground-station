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

#include "channels/channels.h"
#include "util/base_64.h"

using namespace std;

void initSignalHandler();
void signalHandler(int number);

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

    auto messageConverter = make_unique<Json_ApplicationMessageConverter>();
    auto androidMediator = make_unique<ApplicationMediator>(
        params.appParams.receivePort, 
        params.appParams.sendPort,
        move(messageConverter)
    );
    
    auto droneCommunicator = make_unique<DroneCommunicator>();
    GroundStation groundStation(
        move(androidMediator),
        move(droneCommunicator)
    );

    groundStation.run();

    // Test for getting and displaying the image in blc_channels
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

    // auto imageBuffer = pdsChannels::image.uchars;
    // const uint32_t bufferLength = pdsChannels::imageSize.uints32[0];
    // string encodedImage = encode_base64(imageBuffer, bufferLength);
    // cout << encodedImage << endl;

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
        exit(0);
        break;
    case SIGQUIT:
        LOG_F(WARNING, "SIGQUIT caught");
        exit(0);
        break;
    case SIGTERM:
        LOG_F(WARNING, "SIGTERM caught");
        exit(1);
        break;
    case SIGFPE:
        LOG_F(WARNING, "SIGFPE caught");
        exit(2);
        break;
    default:
        LOG_F(WARNING, "Unhandled signal caught : %d", number);
        break;
    }
}