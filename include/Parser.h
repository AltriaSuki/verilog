#include "Token.h"
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include "Ast.h"
#include "Lexer.h"
#pragma once
class Parser{

    private:
    std::vector<Token> tokens;
    size_t currentTokenIndex;
    Token currentToken;
    std::unordered_map<std::string, int> precedence = {
        {"=", 1},
        {"||", 2},
        {"&&", 3},
        {"|", 4},
        {"^", 5},
        {"&", 6},
        {"==", 7}, {"!=", 7},
        {"<", 8}, {"<=", 8}, {">", 8}, {">=", 8},
        {"+", 9}, {"-", 9},
        {"*", 10}, {"/", 10}, {"%", 10}
    };
    
    std::unordered_map<std::string, bool> isRightAssociative = {
        {"=", true},  // 赋值是右结合
        {"+", false}, {"-", false},
        {"*", false}, {"/", false}, {"%", false},
        {"&&", false}, {"||", false},
        {"==", false}, {"!=", false}
        // 其他的可以根据需要添加
    };
    
    
    

    public:
        Parser(Lexer& lexer);
        AstNode* parseProgram();//解析整个文件
        AstNode* parseModuleDeclaration();
        AstNode* parseModuleBody();
        AstNode* parseDeclaration();
        AstNode* parsePortList();
        AstNode* parsePortListTail();
        AstNode* parseDataType();
        AstNode* parseIdentifier();
        AstNode* parseIdentifierTail();
        AstNode* parseStatement();
        AstNode* parseIfStatement();
        AstNode* parseElseStatement();
        AstNode* parseAssignment();
        AstNode* parseInitialStatement();
        AstNode* parseAlwaysStatement();
        AstNode* parseExpression(int minPrec);
        AstNode* parseUnaryExpression();
        AstNode* parseOperator();

};