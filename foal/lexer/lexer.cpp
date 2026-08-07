#include "lexer.hpp"
#include <cctype>
#include <stdexcept>
#include <unordered_map>
namespace unicorn {
namespace {
const std::unordered_map<std::string, TokenType> keywords = {
    {"let",    TokenType::Let},
    {"func",   TokenType::Func},
    {"return", TokenType::Return},
    {"if",     TokenType::If},
    {"else",   TokenType::Else}
};
} // namespace
Lexer::Lexer(const std::string& source)
    : source_(source)
{
}
bool Lexer::isAtEnd() const
{
    return current_ >= source_.size();
}
char Lexer::peek() const
{
    if (isAtEnd())
        return '\0';
    return source_[current_];
}
char Lexer::advance()
{
    if (isAtEnd())
        return '\0';
    char c = source_[current_++];
    if (c == '\n') {
        ++line_;
        column_ = 1;
    } else {
        ++column_;
    }
    return c;
}
void Lexer::skipWhitespace()
{
    while (!isAtEnd()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance();
        } else {
            break;
        }
    }
}
void Lexer::skipComment()
{
    // Single-line comment:
    // // everything until the end of the line
    if (peek() == '/' &&
        current_ + 1 < source_.size() &&
        source_[current_ + 1] == '/') {
        while (!isAtEnd() && peek() != '\n')
            advance();
    }
}
Token Lexer::readIdentifier()
{
    const std::size_t start = current_;
    const std::size_t startColumn = column_;
    while (!isAtEnd()) {
        char c = peek();
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_')
            advance();
        else
            break;
    }
    std::string text = source_.substr(start, current_ - start);
    auto it = keywords.find(text);
    if (it != keywords.end()) {
        return {
            it->second,
            text,
            line_,
            startColumn
        };
    }
    return {
        TokenType::Identifier,
        text,
        line_,
        startColumn
    };
}
Token Lexer::readNumber()
{
    const std::size_t start = current_;
    const std::size_t startColumn = column_;
    while (!isAtEnd() &&
           std::isdigit(static_cast<unsigned char>(peek()))) {
        advance();
    }
    // Decimal part
    if (peek() == '.' &&
        current_ + 1 < source_.size() &&
        std::isdigit(
            static_cast<unsigned char>(source_[current_ + 1]))) {
        advance();
        while (!isAtEnd() &&
               std::isdigit(static_cast<unsigned char>(peek()))) {
            advance();
        }
    }
    return {
        TokenType::Number,
        source_.substr(start, current_ - start),
        line_,
        startColumn
    };
}
Token Lexer::readString()
{
    const std::size_t startColumn = column_;
    // Opening quote
    advance();
    const std::size_t contentStart = current_;
    while (!isAtEnd() && peek() != '"') {
        advance();
    }
    if (isAtEnd()) {
        throw std::runtime_error(
            "Unterminated string at line " +
            std::to_string(line_)
        );
    }
    std::string value =
        source_.substr(contentStart, current_ - contentStart);
    // Closing quote
    advance();
    return {
        TokenType::String,
        value,
        line_,
        startColumn
    };
}
Token Lexer::makeToken(TokenType type,
                       std::size_t start)
{
    return {
        type,
        source_.substr(start, current_ - start),
        line_,
        column_ - (current_ - start)
    };
}
std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        skipWhitespace();
        if (isAtEnd())
            break;
        // Comments
        if (peek() == '/' &&
            current_ + 1 < source_.size() &&
            source_[current_ + 1] == '/') {
            skipComment();
            continue;
        }
        const std::size_t start = current_;
        char c = advance();
        // Identifiers and keywords
        if (std::isalpha(static_cast<unsigned char>(c)) ||
            c == '_') {
            --current_;
            --column_;
            tokens.push_back(readIdentifier());
            continue;
        }
        // Numbers
        if (std::isdigit(static_cast<unsigned char>(c))) {
            --current_;
            --column_;
            tokens.push_back(readNumber());
            continue;
        }
        // Strings
        if (c == '"') {
            --current_;
            --column_;
            tokens.push_back(readString());
            continue;
        }
        switch (c) {
        // Arithmetic
        case '+':
            tokens.push_back(makeToken(TokenType::Plus, start));
            break;
        case '-':
            tokens.push_back(makeToken(TokenType::Minus, start));
            break;
        case '*':
            tokens.push_back(makeToken(TokenType::Star, start));
            break;
        case '%':
            tokens.push_back(makeToken(TokenType::Percent, start));
            break;
        case '/' :
            tokens.push_back(makeToken(TokenType::Slash, start));
            break;
        // Assignment / equality
        case '=':
            if (peek() == '=') {
                advance();
                tokens.push_back(
                    makeToken(TokenType::EqualEqual, start)
                );
            } else {
                tokens.push_back(
                    makeToken(TokenType::Equal, start)
                );
            }
            break;
        // Not / not equal
        case '!':
            if (peek() == '=') {
                advance();
                tokens.push_back(
                    makeToken(TokenType::NotEqual, start)
                );
            } else {
                tokens.push_back(
                    makeToken(TokenType::Not, start)
                );
            }
            break;
        // Less / less equal
        case '<':
            if (peek() == '=') {
                advance();
                tokens.push_back(
                    makeToken(TokenType::LessEqual, start)
                );
            } else {
                tokens.push_back(
                    makeToken(TokenType::Less, start)
                );
            }
            break;
        // Greater / greater equal
        case '>':
            if (peek() == '=') {
                advance();
                tokens.push_back(
                    makeToken(TokenType::GreaterEqual, start)
                );
            } else {
                tokens.push_back(
                    makeToken(TokenType::Greater, start)
                );
            }
            break;
        // Delimiters
        case '(':
            tokens.push_back(
                makeToken(TokenType::LeftParen, start)
            );
            break;
        case ')':
            tokens.push_back(
                makeToken(TokenType::RightParen, start)
            );
            break;
        case '{':
            tokens.push_back(
                makeToken(TokenType::LeftBrace, start)
            );
            break;
        case '}':
            tokens.push_back(
                makeToken(TokenType::RightBrace, start)
            );
            break;
        case '[':
            tokens.push_back(
                makeToken(TokenType::LeftBracket, start)
            );
            break;
        case ']':
            tokens.push_back(
                makeToken(TokenType::RightBracket, start)
            );
            break;
        case ',':
            tokens.push_back(
                makeToken(TokenType::Comma, start)
            );
            break;
        case ':':
            tokens.push_back(
                makeToken(TokenType::Colon, start)
            );
            break;
        case ';':
            tokens.push_back(
                makeToken(TokenType::Semicolon, start)
            );
            break;
        default:
            tokens.push_back(
                makeToken(TokenType::Unknown, start)
            );
            break;
        }
    }
    tokens.push_back({
        TokenType::EndOfFile,
        "",
        line_,
        column_
    });
    return tokens;
}
} // namespace unicorn
