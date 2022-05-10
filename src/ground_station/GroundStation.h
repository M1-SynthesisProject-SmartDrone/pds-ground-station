#ifndef __GROUNDSTATION_H__
#define __GROUNDSTATION_H__

#include "application/network/ApplicationMediator.h"

/**
 * The main class that will handle everything in the server
 */
class GroundStation
{
private:
    bool m_isRunning = true;

    std::unique_ptr<ApplicationMediator> m_applicationMediator;

public:
    GroundStation(
        std::unique_ptr<ApplicationMediator> applicationMediator
    );
    ~GroundStation();

    /**
     * The main entry-point method. This is gobally an infinite while loop
     */
    void run();

    void askStopRunning();
};

#endif // __GROUNDSTATION_H__