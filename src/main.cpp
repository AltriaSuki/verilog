#include"Lexer.h"
#include"Parser.h"
#include"RTLILGen.h"
#include"Optimization.h"
#include"rtlil_to_dot.h"
#include"ILP.h"
#include"Node.h"
int main(){
    Lexer lexer("module test(a,b,c) wire e; assign a=~b; endmodule");
    Parser parser(lexer);
    AstNode* node=parser.parseProgram();
    // Optimization opt=Optimization(node);
    // opt.optimize_in_Ast();
    node->print(0);
    RTLILGen rtlil(node);
    std::string result=rtlil.generateRTLIL();
    // opt.set_rtlil_code(result);
    // opt.optimize_in_rtlil();
    // result=opt.get_optimized_rtlil();
    std::cout<<result<<std::endl;
    // ILP ilp;
    // std::string filename="./input/sample.blif";
    // ilp.set_delay_map({{"AND",1},{"OR",1},{"NOT",1}});
    // ilp.read_blif(filename);
    // std::map<std::string,int> constraints;
    // constraints["AND"]=2;
    // constraints["OR"]=1;
    // constraints["NOT"]=2;
    // ilp.make_constraints(constraints);
    return 0;
}

