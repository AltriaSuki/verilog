#include"Lexer.h"

int main(){
    Lexer lexer("module adder(a,b,c); assign c ==== a + b; endmodule");
    Token token = lexer.NextToken();
    while(token.type != END_OF_INPUT){
        token.print();
        token = lexer.NextToken();
    }
    return 0;
}