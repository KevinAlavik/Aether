#include <iostream>

#include <utils/logger.hpp>

Aether::Logger mainLogger("main", "Aether");

int main()
{
    mainLogger.log(Aether::LogLevel::OK, "Hello world!");
    return 0;
}