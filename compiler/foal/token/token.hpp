#pragma once

#include <cstddef>
#include <string>

namespace unicorn {

enum class TokenType {
    // Literals
    Identifier,
    Number,
    String,

    // Keywords
    Let,
    Func,
    Return,
    If,
    Else,

    // Arithmetic
    Plus,
    Minus,
    Star,
    Slash,
    Percent,

    // Comparison
    Equal,
    EqualEqual,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,

    // Logical
    And,
    Or,
    Not,

    // Delimiters
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    LeftBracket,
    RightBracket,

    Comma,
    Colon,
    Semicolon,

    // Special
    EndOfFile,
    Unknown
};

struct Token {
    TokenType type;
    std::string lexeme;
    std::size_t line;
    std::size_t column;
};

} // namespace unicorn
