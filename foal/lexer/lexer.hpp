#pragma once

#include "../token/token.hpp"

#include <string>
#include <vector>

namespace unicorn {

class Lexer
{
public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:
    char peek() const;
    char advance();
    bool isAtEnd() const;

    void skipWhitespace();
    void skipComment();

    Token readIdentifier();
    Token readNumber();
    Token readString();

    Token makeToken(TokenType type,
                    std::size_t start);

private:
    std::string source_;
    std::size_t current_ = 0;
    std::size_t line_ = 1;
    std::size_t column_ = 1;
};

} // namespace unicorn
