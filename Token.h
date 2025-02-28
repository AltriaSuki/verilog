#pragma once

#include <string>

enum TokenType{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    NUMBER,
    SEPARATOR,
    END_OF_INPUT,
    BRACKET
};

class Token{
    public:
        TokenType type;
        std::string value;

        Token(TokenType type, std::string value):type(type),value(value){}
        void print();
};