#include"Lexer.h"
#include"Parser.h"
int main(){
    Lexer lexer("module test(a,b,c) ; assign a=b+c; endmodule");
    Parser parser(lexer);
    AstNode* node=parser.parseProgram();
    node->print(0);
    return 0;
}

