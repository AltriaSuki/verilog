#include "Token.h"
#include<iostream>
#include<string>
#include<vector>
#include "Ast.h"
#include "Lexer.h"
class Parser{

    private:
    std::vector<Token> tokens;
    size_t currentTokenIndex;
    Token currentToken;

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
        AstNode* parseExpression(int level=0);
        AstNode* parseBinaryExpression();
        AstNode* parseUnaryExpression();
        AstNode* parseOperator();

};