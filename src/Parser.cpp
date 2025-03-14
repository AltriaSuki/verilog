#include"Parser.h"
#include"Token.h"

Parser::Parser(Lexer& lexer){
    Token token=lexer.NextToken();
    while(token.type!=END_OF_INPUT){
        tokens.push_back(token);
        token=lexer.NextToken();
    }
    tokens.push_back(token);//push back the END_OF_INPUT token
    currentTokenIndex=0;
    currentToken=tokens[currentTokenIndex];
}

AstNode* Parser::parseProgram(){
    AstNode* node=new AstNode();
    node->value="program";
    while(currentToken.type!=END_OF_INPUT){
        AstNode* child=parseModuleDeclaration();
        if(child!=nullptr){
            node->children.push_back(child);
        }
    }
    return node;
}

AstNode* Parser::parseModuleDeclaration(){
    if(currentToken.type==KEYWORD&&currentToken.value=="module"){
        AstNode* node=new AstNode();
        node->value="module";
        currentToken=tokens[++currentTokenIndex];
        if(currentToken.type==IDENTIFIER){
            node->value+=currentToken.value;
            currentToken=tokens[++currentTokenIndex];
        }
        AstNode* child=parsePortList();
        if(child!=nullptr){
            node->children.push_back(child);
        }
    }else{
        std::cout<<"Error: Expected module declaration"<<std::endl;
        return nullptr;
    }
}