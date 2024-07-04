#include <core/tokenizing.hpp>
#include <aether.hpp>

std::vector<Aether::Token> Aether::Tokenizer::tokenize(const std::string &src)
{
    std::vector<std::string> words = Aether::Strings::split(src, " ");
    for (std::string token : words)
    {
        mainLogger.log(Aether::LogLevel::DEBUG, "Tokenizing: " + token);
    }

    return std::vector<Token>();
}