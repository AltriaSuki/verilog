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
    int add_num=0;
    int sub_num=0;
    int mul_num=0;
    int div_num=0;
    int mod_num=0;
    int and_num=0;
    int or_num=0;
    int xor_num=0;
    int not_num=0;
    int temp_id=0;
    int incre_num(std::string op);
    void expression_toRTLIL(AstNode* node);
    std::string new_temp(){
        return "tmp"+std::to_string(++temp_id);
    }
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
};