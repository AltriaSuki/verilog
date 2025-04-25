

#include<string>
#include"Parser.h"
#include"helper.h"
#include"RTLILGen.h"
#include"Ast.h"


class Optimization{
    std::string rtlil_code;
    std::string optimized_code;
    AstNode* root;
    AstNode* constant_folding(AstNode* nodes);
    void dead_code_elimination();
    void common_subexpression_elimination();

    
public:
    Optimization(AstNode* root):root(root){}//某些优化不需要rtlil_code
    void set_rtlil_code(std::string rtlil);
    void optimize_in_Ast();
    void optimize_in_rtlil();
    std::string get_optimized_Ast();
    std::string get_optimized_rtlil();
};