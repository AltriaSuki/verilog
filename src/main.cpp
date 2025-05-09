#include"Lexer.h"
#include"Parser.h"
#include"RTLILGen.h"
#include"Optimization.h"
int main(){
    Lexer lexer("module test(a,b,c) wire e; assign a=b*c+d;assign e=b*c+f; endmodule");
    Parser parser(lexer);
    AstNode* node=parser.parseProgram();
    Optimization opt=Optimization(node);
    opt.optimize_in_Ast();
    node->print(0);
    RTLILGen rtlil(node);
    std::string result=rtlil.generateRTLIL();
    opt.set_rtlil_code(result);
    opt.optimize_in_rtlil();
    std::cout<<result<<std::endl;
    return 0;
}

