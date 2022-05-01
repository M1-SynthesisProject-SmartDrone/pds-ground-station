#include <iostream>
#include <errno.h>
#include <thread>
#include <vector>
#include <random>
#include <stdexcept>
#include <filesystem>
#include <stdlib.h>
#include <sstream>

#include <loguru/loguru.hpp>

#include "config/ConfigParams.h"
#include "config/ConfigParser.h"

using namespace std;

/**
 * THIS APPLICATION MUST BE LAUNCHED AFTER THE DRONE INTERFACE ONE 
 * (or another program that opens the channels)
 */
int main(int argc, char* argv[])
{
    loguru::init(argc, argv);
    LOG_F(INFO, "Start the 'SmartDroneController' application");

    ConfigParser configParser(argc, argv);
    ConfigParams params = configParser.parse();


    // LOG_F(INFO, "%ld threads stored", threads.size());
    // for (auto& thread : threads)
    // {
    //     thread->start();
    // }

    // for (auto& thread : threads)
    // {
    //     thread->join();
    // }

    return EXIT_SUCCESS;
}