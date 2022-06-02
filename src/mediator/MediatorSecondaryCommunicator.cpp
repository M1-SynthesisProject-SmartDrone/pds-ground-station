#include "MediatorSecondaryCommunicator.h"

#include <iostream>
#include <iomanip>
#include <ctime>

#include <nlohmann/json.hpp>

#include "util/memory_utils.hpp"

using namespace std;

MediatorSecondaryCommunicator::MediatorSecondaryCommunicator(std::string host, uint16_t port):
    m_channel(host, port)
{
    
}

MediatorSecondaryCommunicator::~MediatorSecondaryCommunicator()
{}

vector<Coordinates> MediatorSecondaryCommunicator::fetchAllCheckpoints()
{
    auto socket = m_channel.getTcpSocket();
    
    // Request all checkpoints
    nlohmann::json reqTrPoints = {
        {"requestType", "REQ_TR_POINTS"}
    };
    socket->sendMessage(reqTrPoints.dump());

    // Get the intermediary response
    auto respTrPoints = nlohmann::json::parse(socket->receiveMessage());
    long fileSize = respTrPoints["filesize"];

    // Say that we are ready to register the image
    nlohmann::json reqWaitFile = {
        {"requestType", "WAIT_TR_FILE"}
    };
    socket->sendMessage(reqWaitFile.dump());

    // Receive the big string and parse it
    auto msgAllCheckpoints = socket->receiveBigMessage<char>(fileSize);
    auto finalResp = nlohmann::json::parse(string(msgAllCheckpoints.begin(), msgAllCheckpoints.end()));

    // We can now create our vector of coordinates
    auto jsonArray = finalResp["content"];
    vector<Coordinates> coordinatesVector;
    coordinatesVector.reserve(jsonArray.size());
    for (const auto& elt : jsonArray)
    {
        Coordinates coords(elt["lat"], elt["lon"], elt["height"], elt["rotation"]);
        coordinatesVector.push_back(coords);
    }
    return coordinatesVector;
}

tuple<int, vector<unsigned char>> MediatorSecondaryCommunicator::fetchNextCheckpoint()
{
    
}
