#include <iostream>
#include <string>
#include <vector>

#include <utils/logger.hpp>
#include <utils/file.hpp>
#include <utils/string.hpp>

Aether::Logger mainLogger("main", "AetherMain");

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        mainLogger.log(Aether::LogLevel::ERROR, "Usage: " + std::string(argv[0]) + " <source_file>");
        return 1;
    }

    Aether::File file(argv[1]);
    try
    {
        file.open(Aether::File::OpenMode::READ);

        std::vector<char> fileData = file.readAll();
        std::string content = std::string(fileData.begin(), fileData.end());

        // TODO: Tokenizing bruh
        // TODO: Lexing bruh
        // TODO: Parsing bruh
        // TODO: Semantic analysis bruh
        // TODO: Code generation bruh

        std::vector<std::string> lines = Aether::Strings::split(content, "\n");

        for (std::string line : lines)
        {
            mainLogger.log(Aether::LogLevel::DEBUG, line);
        }

        file.close();
    }
    catch (const Aether::FileException &e)
    {
        mainLogger.log(Aether::LogLevel::FATAL, "FileException(" + std::string(e.what()) + ")");
        return 1;
    }
    return 0;
}
