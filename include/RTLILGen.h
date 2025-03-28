#include"Parser.h"
#include"Token.h"
#include<vector>
#include<string>
#include<unordered_set>
#include "Ast.h"
#pragma once

class RTLILGen{
private:
    AstNode* root;
    std::string result;
    std::unordered_set<std::string> portList;
public:
    RTLILGen(AstNode* root):root(root){}
    std::string generateRTLIL();
    void generatePortList(AstNode* node);
    void generateModuleBody(AstNode* node);
    void generateDeclaration(AstNode* node);
    void generateStatement(AstNode* node);
    void generateAssignment(AstNode* node);
    void generateIfStatement(AstNode* node);
    void generateElseStatement(AstNode* node);
    void generateAlwaysStatement(AstNode* node);
    void generateInitialStatement(AstNode* node);
    void generateExpression(AstNode* node);
    void generateBinaryExpression(AstNode* node);
    void generateUnaryExpression(AstNode* node);
};