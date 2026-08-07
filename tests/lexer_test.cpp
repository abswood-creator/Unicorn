#include "../compiler/foal/lexer/lexer.hpp"

#include <cassert>
#include <iostream>

using namespace unicorn;

int main()
{
    const std::string source = R"(
        // A tiny Unicorn program
        let x = 42;
        let y = x + 3.14;
        let message = "Hello, Unicorn!";
    )";

    Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // let
    assert(tokens[0].type == TokenType::Let);
    assert(tokens[0].lexeme == "let");

    // x
    assert(tokens[1].type == TokenType::Identifier);
    assert(tokens[1].lexeme == "x");

    // =
    assert(tokens[2].type == TokenType::Equal);

    // 42
    assert(tokens[3].type == TokenType::Number);
    assert(tokens[3].lexeme == "42");

    // ;
    assert(tokens[4].type == TokenType::Semicolon);

    // let
    assert(tokens[5].type == TokenType::Let);

    // y
    assert(tokens[6].type == TokenType::Identifier);
    assert(tokens[6].lexeme == "y");

    // =
    assert(tokens[7].type == TokenType::Equal);

    // x
    assert(tokens[8].type == TokenType::Identifier);
    assert(tokens[8].lexeme == "x");

    // +
    assert(tokens[9].type == TokenType::Plus);

    // 3.14
    assert(tokens[10].type == TokenType::Number);
    assert(tokens[10].lexeme == "3.14");

    // ;
    assert(tokens[11].type == TokenType::Semicolon);

    // let
    assert(tokens[12].type == TokenType::Let);

    // message
    assert(tokens[13].type == TokenType::Identifier);
    assert(tokens[13].lexeme == "message");

    // =
    assert(tokens[14].type == TokenType::Equal);

    // string
    assert(tokens[15].type == TokenType::String);
    assert(tokens[15].lexeme == "Hello, Unicorn!");

    // ;
    assert(tokens[16].type == TokenType::Semicolon);

    // End
    assert(tokens[17].type == TokenType::EndOfFile);

    std::cout << "🦄 Lexer tests passed!\n";

    return 0;
}
