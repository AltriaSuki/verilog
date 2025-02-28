#pragma once
#include "Token.h"

#include <string>
#include <unordered_set>
class Lexer {
    public:
        explicit Lexer(const std::string& input) : input(input), position(0) {}
        Token NextToken();
        void advance();
        Token parseIdentifier();
        Token parseNumber();
        Token parseOperator();
        Token parseSeparator();
        std::string GetWholeExpression();
        //Token GetTokenFromSubExpression(string str);
    private:
        char currentChar;
        const std::string input;
        size_t position;
        std::unordered_set<std::string> keywords = { "module", "input", "output", "wire", "assign", "endmodule" };
    };