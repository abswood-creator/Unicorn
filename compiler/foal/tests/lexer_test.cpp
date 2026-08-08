#include "../lexer/lexer.hpp"

#include <cassert>
#include <iostream>

using namespace unicorn;

const char* tokenName(TokenType type)
{
    switch (type) {
        case TokenType::Identifier:   return "Identifier";
        case TokenType::Number:       return "Number";
        case TokenType::String:       return "String";

        case TokenType::Let:          return "Let";
        case TokenType::Func:         return "Func";
        case TokenType::Return:       return "Return";
        case TokenType::If:           return "If";
        case TokenType::Else:         return "Else";

        case TokenType::Plus:         return "Plus";
        case TokenType::Minus:        return "Minus";
        case TokenType::Star:         return "Star";
        case TokenType::Slash:        return "Slash";
        case TokenType::Percent:      return "Percent";

        case TokenType::Equal:        return "Equal";
        case TokenType::EqualEqual:   return "EqualEqual";
        case TokenType::NotEqual:     return "NotEqual";
        case TokenType::Less:         return "Less";
        case TokenType::LessEqual:    return "LessEqual";
        case TokenType::Greater:      return "Greater";
        case TokenType::GreaterEqual: return "GreaterEqual";

        case TokenType::And:          return "And";
        case TokenType::Or:           return "Or";
        case TokenType::Not:          return "Not";

        case TokenType::LeftParen:    return "LeftParen";
        case TokenType::RightParen:   return "RightParen";
        case TokenType::LeftBrace:    return "LeftBrace";
        case TokenType::RightBrace:   return "RightBrace";
        case TokenType::LeftBracket:  return "LeftBracket";
        case TokenType::RightBracket: return "RightBracket";

        case TokenType::Comma:        return "Comma";
        case TokenType::Colon:        return "Colon";
        case TokenType::Semicolon:    return "Semicolon";

        case TokenType::EndOfFile:    return "EndOfFile";
        case TokenType::Unknown:      return "Unknown";
    }

    return "Unknown";
}

int main()
{
    const std::string source = R"(
        // Keywords and identifiers
        let x = 42;
        let number = 3.14;
        let message = "Hello, Unicorn!";

        func main() {
            if (x >= 10) {
                return x + 1;
            } else {
                return 0;
            }
        }

        // Operators
        x + number;
        x - number;
        x * number;
        x / number;
        x % 2;

        x == 42;
        x != 0;
        x < 100;
        x <= 100;
        x > 1;
        x >= 1;

        // Delimiters
        (x);
        { x };
        [x];
        x, number;
        x: number;
    )";

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    for (std::size_t n = 0; n < tokens.size(); ++n) {
        std::cout
            << n
            << ": "
            << static_cast<int>(tokens[n].type)
            << " -> \""
            << tokens[n].lexeme
            << "\"\n";
    }

    std::size_t i = 0;

    // ------------------------------------------------------------
    // Keywords
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Let);
    assert(tokens[i++].lexeme == "let");

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "x");

    assert(tokens[i].type == TokenType::Equal);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "42");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // ------------------------------------------------------------
    // Decimal number
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Let);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "number");

    assert(tokens[i].type == TokenType::Equal);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "3.14");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // ------------------------------------------------------------
    // String
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Let);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "message");

    assert(tokens[i].type == TokenType::Equal);
    ++i;

    assert(tokens[i].type == TokenType::String);
    assert(tokens[i++].lexeme == "Hello, Unicorn!");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // ------------------------------------------------------------
    // Function
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Func);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "main");

    assert(tokens[i].type == TokenType::LeftParen);
    ++i;

    assert(tokens[i].type == TokenType::RightParen);
    ++i;

    assert(tokens[i].type == TokenType::LeftBrace);
    ++i;

    // ------------------------------------------------------------
    // if
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::If);
    ++i;

    assert(tokens[i].type == TokenType::LeftParen);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "x");

    assert(tokens[i].type == TokenType::GreaterEqual);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "10");

    assert(tokens[i].type == TokenType::RightParen);
    ++i;

    // ------------------------------------------------------------
    // return x + 1
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::LeftBrace);
    ++i;

    assert(tokens[i].type == TokenType::Return);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "x");

    assert(tokens[i].type == TokenType::Plus);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "1");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::RightBrace);
    ++i;

    // ------------------------------------------------------------
    // else
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Else);
    ++i;

    // ------------------------------------------------------------
    // Arithmetic operators
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::LeftBrace);
    ++i;

    assert(tokens[i].type == TokenType::Return);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "0");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::RightBrace);
    ++i;

    assert(tokens[i].type == TokenType::RightBrace);
    ++i;

    // ------------------------------------------------------------
    // More operators
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Plus);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Minus);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Star);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Slash);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Percent);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "2");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // ------------------------------------------------------------
    // Comparison operators
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::EqualEqual);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "42");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::NotEqual);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "0");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Less);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "100");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::LessEqual);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "100");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::Greater);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "1");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::GreaterEqual);
    ++i;

    assert(tokens[i].type == TokenType::Number);
    assert(tokens[i++].lexeme == "1");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // ------------------------------------------------------------
    // Delimiters
    // ------------------------------------------------------------

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::LeftParen);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::RightParen);
    ++i;

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::LeftBrace);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::RightBrace);
    ++i;

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    assert(tokens[i].type == TokenType::LeftBracket);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    ++i;

    assert(tokens[i].type == TokenType::RightBracket);
    ++i;

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // x, number;
    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "x");

    assert(tokens[i].type == TokenType::Comma);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "number");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // x: number;
    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "x");

    assert(tokens[i].type == TokenType::Colon);
    ++i;

    assert(tokens[i].type == TokenType::Identifier);
    assert(tokens[i++].lexeme == "number");

    assert(tokens[i].type == TokenType::Semicolon);
    ++i;

    // End of file
    assert(tokens[i].type == TokenType::EndOfFile);

    std::cout << "🦄 All lexer tests passed!\n";

    return 0;
}
