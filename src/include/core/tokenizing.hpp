#pragma once

#include <string>
#include <vector>
#include <utils/string.hpp>

namespace Aether
{
    enum TokenType
    {
    };

    class Token
    {
        TokenType type;
        std::string lexeme;
    };

    class Tokenizer
    {
    public:
        std::vector<Token> tokenize(const std::string &src);
    };
}