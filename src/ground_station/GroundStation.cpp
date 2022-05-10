#include "GroundStation.h"

#include <loguru/loguru.hpp>

using namespace std;

GroundStation::GroundStation(std::unique_ptr<ApplicationMediator> applicationMediator)
{
    m_applicationMediator = move(applicationMediator);
}

GroundStation::~GroundStation()
{}

void GroundStation::run()
{
    LOG_F(INFO, "Entering the server main loop");
    while(m_isRunning)
    {

    }
}

void GroundStation::askStopRunning()
{
    m_isRunning = false;
}