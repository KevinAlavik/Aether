#include <utils/logger.hpp>

#include <iostream>
#include <chrono>
#include <iomanip>

using namespace Aether;

void Logger::log(LogLevel level, const std::string &message)
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%H:%M:%S");

    std::string color;
    switch (level)
    {
    case OK:
        color = "\033[32m";
        break;
    case WARNING:
        color = "\033[33m";
        break;
    case ERROR:
        color = "\033[31m";
        break;
    case FATAL:
        color = "\033[1;31m";
        break;
    case DEBUG:
        color = "\033[36m";
        break;
    case INFO:
        color = "\033[0;34m";
        break;
    case TRACE:
        color = "\033[0;37m";
        break;
    default:
        color = "\033[0m";
        break;
    }

    std::cout << "[" << ss.str() << "] [" << m_main << "/" << levelToString(level) << "] [" << m_name << "]: "
              << color << message << "\033[0m" << std::endl;
}