
#include<map>
#include<string>
#include"Parser.h"
#include"helper.h"
#include"RTLILGen.h"
#include"Ast.h"
#include<sstream>


class Optimization{

    struct info{
        bool in_cell;
        std::string cell_name;
        std::string cell_type;
        //这个是在cell中使用的变量
        std::string A;
        std::string B;
        std::string Y;
        std::string S;
        //这个是非cell中使用的变量
        //比如 connect \m \a 就是将m赋值给a
        std::string input;
        std::string output;
    };

    struct whole_info{
        std::string whole_info;
        info block_info;
        bool is_opration;
    };
    std::string rtlil_code;
    std::string optimized_code;
    std::vector<whole_info*> whole_blocks;//存储整个块的信息//还应该包含最初的声明信息
    AstNode* root;
    AstNode* constant_folding(AstNode* nodes);
    void dead_code_elimination();
    void common_subexpression_elimination();
    void divide_into_blocks();
    
public:
    Optimization(AstNode* root):root(root){}//某些优化不需要rtlil_code
    void set_rtlil_code(std::string rtlil);
    void optimize_in_Ast();
    void optimize_in_rtlil();
    std::string get_optimized_Ast();
    std::string get_optimized_rtlil();
};