#include"Lexer.h"
#include"Parser.h"
#include"RTLILGen.h"
int main(){
    Lexer lexer("module test(a,b,c) wire e; if(m) assign a=c; endmodule");
    Parser parser(lexer);
    AstNode* node=parser.parseProgram();
    node->print(0);
    RTLILGen rtlil(node);
    std::string result=rtlil.generateRTLIL();
    std::cout<<result<<std::endl;
    return 0;
}

