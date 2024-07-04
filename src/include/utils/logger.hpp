#pragma once

#include <string>

namespace Aether
{
    enum LogLevel
    {
        OK,
        WARNING,
        ERROR,
        FATAL,
        DEBUG,
        INFO,
        TRACE
    };

    class Logger
    {
    public:
        Logger(const std::string &m, const std::string &n) : m_name(n), m_main(m) {}
        void log(LogLevel level, const std::string &message);

    private:
        const std::string m_name;
        const std::string m_main;

        const std::string levelToString(LogLevel level)
        {
            switch (level)
            {
            case OK:
                return "OK";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case FATAL:
                return "FATAL";
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case TRACE:
                return "TRACE";
            default:
                return "UNKNOWN";
            }
        }
    };
}