#include "MediatorSecondaryCommunicator.h"

#include "util/memory_utils.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

MediatorSecondaryCommunicator::MediatorSecondaryCommunicator(std::string host, uint16_t port):
    m_channel(host, port)
{
    
}

MediatorSecondaryCommunicator::~MediatorSecondaryCommunicator()
{}
