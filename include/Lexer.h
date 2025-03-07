#pragma once
#include "Token.h"

#include <string>
#include <unordered_set>
class Lexer {
    public:
        explicit Lexer(const std::string& input) : input(input), position(0) {
            currentChar = input[position];
        }
        Token NextToken();
        void advance();
        Token parseIdentifier();
        Token parseNumber();
        Token parseOperator();
        Token parseSeparator();
        Token parseBracket();
        void skipComment();
        void skipWhitespace();
        std::string GetWholeExpression();
        //Token GetTokenFromSubExpression(string str);
    private:
        char currentChar;
        const std::string input;
        size_t position;
        std::unordered_set<std::string> keywords = { "module","if","else","begin","end" "reg","integer","parameter","initial","always","input", "output", "wire", "assign", "endmodule" };
        std::unordered_set<std::string> operators=
        {"+","-","*","/","%","==","!=","<",">","<=",">=","&&","||","!","&","|","^","<<",">>","~","="};
    };