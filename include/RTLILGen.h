
#include"Parser.h"

#include"Token.h"
#include<vector>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include "Ast.h"
#pragma once

class RTLILGen {
private:
    AstNode* root;
    std::string result;
    std::unordered_set<std::string> portList;
    int processID = 0;
    std::vector<std::string> AlwaysVar;
    std::string resultInAlways;
    std::string resultInInitial;
    int add_num = 0;
    int sub_num = 0;
    int mul_num = 0;
    int div_num = 0;
    int mod_num = 0;
    int and_num = 0;
    int or_num = 0;
    int xor_num = 0;
    int not_num = 0;
    int temp_id = 0;
    int eq_num = 0;
    int ne_num = 0;
    int lt_num = 0;
    int le_num = 0;
    int gt_num = 0;
    int ge_num = 0;
    int mux_num = 0;
    int incre_num(std::string op);
    void assign_helper(AstNode* node);
    std::string new_temp() {
        return "tmp" + std::to_string(++temp_id);
    }
public:
    RTLILGen(AstNode* root) :root(root) {}
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

   //new1.0
    void getAlwaysVariable(AstNode* node);
    void generateAlwaysStatementType1(AstNode* node);

  

};