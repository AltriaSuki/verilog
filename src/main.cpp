#include"Lexer.h"
#include"Parser.h"
int main(){
    Lexer lexer("\0");
    Parser parser(lexer);
    AstNode* node=parser.parseProgram();
    node->print(0);
    return 0;
}