
#include "JsonTokenizer.hpp"

Tokenizer::Tokenizer(std::string_view json) : input{json} {}

bool Tokenizer::isCurrentDigit() const {
    return std::isdigit(static_cast<unsigned char>(peek()));
}

bool Tokenizer::isCurrentAlpha() const {
    return std::isalpha(static_cast<unsigned char>(peek()));
}

bool Tokenizer::isCurrentAlpha(char c) const {
    return std::isalpha(static_cast<unsigned char>(c));
}

bool Tokenizer::isCurrentSpace() const {
    return std::isspace(static_cast<unsigned char>(peek()));
}

char Tokenizer::peek() const
{
    return pos < input.size() ? input[pos] : '\0';
}

char Tokenizer::advance()
{
    if (pos >= input.size())
        return '\0';
    char c = input[pos++];
    if (c == '\n') {
        line++;
        column = 1;
    } else
        column++;
    return c;
}

void Tokenizer::skipWhitespace()
{
    while (isCurrentSpace()) {
        advance();
    }
}

char Tokenizer::parseEscape(char escaped) const
{
    switch (escaped) {
        case '"':  return '"';
        case '\\': return '\\';
        case '/':  return '/';
        case 'b':  return '\b';
        case 'f':  return '\f';
        case 'n':  return '\n';
        case 'r':  return '\r';
        case 't':  return '\t';
        default:   return '\0';
    }
}

Token Tokenizer::parseString()
{
    Token token{TokenType::STRING, "", line, column};
    advance();
    char c = peek();
    while (c != '"' && c != '\0') {
        if (c == '\\') {
            advance();
            char escaped = parseEscape(advance());
            if (escaped == '\0') {
                token.type = TokenType::ERROR;
                return token;
            }
            token.value += escaped;
        } else {
            token.value += c;
            advance();
        }
        c = peek();
    }
    if (c == '"')
        advance();
    else
        token.type = TokenType::ERROR;
    return token;
}

Token Tokenizer::parseNumber()
{
    Token token{TokenType::NUMBER, "", line, column};

    if (peek() == '-')
        token.value += advance();

    while (isCurrentDigit())
        token.value += advance();

    if (peek() == '.') {
        token.value += advance();
        while (isCurrentDigit())
            token.value += advance();
    }

    return token;
}

Token Tokenizer::parseKeyword() {
    Token token{TokenType::ERROR, "", line, column};

    while (isCurrentAlpha())
        token.value += advance();

    if (token.value == "true") {
        token.type = TokenType::TRUE;
    } else if (token.value == "false") {
        token.type = TokenType::FALSE;
    } else if (token.value == "null") {
       token.type = TokenType::NULL_TYPE;
    } else
        token.value = "Unknown keyword: " + token.value;
    return token;
}

Token Tokenizer::makeSimpleToken(TokenType type, char c)
{
    Token token{type, std::string(1, c), line, column};
    advance();
    return token;
}

Token Tokenizer::parseToken(char c)
{
    switch (c) {
        case '{':
            return makeSimpleToken(TokenType::LBRACE, '{');
        case '}':
            return makeSimpleToken(TokenType::RBRACE, '}');
        case '[':
            return makeSimpleToken(TokenType::LBRACKET, '[');
        case ']':
            return makeSimpleToken(TokenType::RBRACKET, ']');
        case ':':
            return makeSimpleToken(TokenType::COLON, ':');
        case ',':
            return makeSimpleToken(TokenType::COMMA, ',');
        case '"':
            return parseString();
        case '-':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return parseNumber();
        default: {
            if (isCurrentAlpha(c)) {
                return parseKeyword();
            } else {
                Token token{TokenType::ERROR, std::string(1, c), line, column};
                advance();
                return token;
            }
        }
    }
}

std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> tokens;
    while (peek() != '\0') {
        skipWhitespace();
        char c = peek();
        if (c == '\0') break;

        tokens.push_back(parseToken(c));
    }
    tokens.push_back({TokenType::EOF_TYPE, "", line, column});
    return tokens;
}