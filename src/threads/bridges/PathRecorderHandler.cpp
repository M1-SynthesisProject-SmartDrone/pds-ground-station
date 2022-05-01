
#include "threads/bridges/PathRecorderHandler.h"

#include <loguru/loguru.hpp>

using namespace std;
namespace fs = std::filesystem;

PathRecorderHandler::PathRecorderHandler(std::string baseFolderName): m_baseFolderPath(baseFolderName)
{
    // Create baseFolder if not exists
    LOG_F(INFO, "Check if folder exists at %s", fs::absolute(m_baseFolderPath).c_str());
    if(!fs::exists(m_baseFolderPath) || !fs::is_directory(m_baseFolderPath))
    {
        LOG_F(INFO, "Create path recorder tmp folder");
        fs::create_directories(m_baseFolderPath);
    }
}

PathRecorderHandler::~PathRecorderHandler()
{}

void PathRecorderHandler::startRecording()
{
    // ! Thread safe (can slow down processes ?) !
    unique_lock<mutex> lock(m_lock);
    if (m_isRecording)
    {
        throw runtime_error("A recording is already in progress");
    }
    // Create random filename and assign to base folder
    // Very unlikely to already have a file with this name, but never say never
    do {
        string baseName = createRandomString() + ".csv";
        fs::path filePath(baseName);
        m_currentFilePath = m_baseFolderPath / filePath;
    } while (fs::exists(m_currentFilePath));
    
    // Open file and write headers
    m_isRecording = true;
    m_currentStream.open(m_currentFilePath.string());
    // Do NOT call std::endl, as it forces to flush, thus affecting performances
    m_currentStream << "lat;lon;alt\n"; 
}

std::string PathRecorderHandler::stopRecording()
{
    unique_lock<mutex> lock(m_lock);
    if(!m_isRecording)
    {
        throw runtime_error("No recording is planned");
    }
    m_isRecording = false;
    // Flush automatically remaining data
    m_currentStream.close();
    return fs::absolute(m_currentFilePath).string();
}

void PathRecorderHandler::insertData(int32_t latitude, int32_t longitude, int32_t altitude)
{
    unique_lock<mutex> lock(m_lock);
    if (m_isRecording)
    {
        // For lat and lon, we need to add a decimal point after the second digit
        string latStr = intToCoordinate(latitude);
        string lonStr = intToCoordinate(longitude);
        // Do NOT call std::endl, as it forces to flush, thus affecting performances
        m_currentStream << latStr << ';' << lonStr << ';' << altitude << '\n';
    }
}

bool PathRecorderHandler::isRecording()
{
    return m_isRecording;
}

string PathRecorderHandler::createRandomString()
{
    string str(NAME_LENGTH, 0);
    generate_n(str.begin(), NAME_LENGTH, randomChar);
    return str;
}

string PathRecorderHandler::intToCoordinate(int32_t n)
{
    // max length of coordinate is 9 digits (+ count the '\0' character)
    char buffer[10];
    snprintf(buffer, 9, "%08d", n);
    string numStr(buffer);

    // From char 0, take 2 chars
    string intPart = numStr.substr(0, 2);
    // From char 2, take all remaining chars
    string decimalPart = numStr.substr(2);

    return intPart + "." + decimalPart;
}
