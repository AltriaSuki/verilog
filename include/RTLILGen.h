#include"Parser.h"
#include"Token.h"
#include<vector>
#include<string>
#include "Ast.h"
class RTLILGen{
private:
    AstNode* root;
    std::vector<std::string> result;
public:
    RTLILGen(AstNode* root):root(root){}
    std::vector<std::string> generateRTLIL();
};