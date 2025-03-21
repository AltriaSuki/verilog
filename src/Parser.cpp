#include"Parser.h"
#include"Token.h"
#include"helper.h"

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
    node->type="program";
    while(currentToken.type!=END_OF_INPUT){
        AstNode* child=parseModuleDeclaration();
        if(child!=nullptr){
            node->children.push_back(child);
        }
        AstNode* child2=new AstNode();

        child2->value=currentToken.value;
        child2->type="endmodule";
        currentToken=tokens[++currentTokenIndex];
        node->children.push_back(child2);
    }
    
    return node;
}

AstNode* Parser::parseModuleDeclaration(){
    if(currentToken.type==KEYWORD&&currentToken.value=="module"){
        AstNode* node=new AstNode();
        node->value="module";
        node->type="module";
        currentToken=tokens[++currentTokenIndex];
        if(currentToken.type==IDENTIFIER){
            node->value+=currentToken.value;
            currentToken=tokens[++currentTokenIndex];
        }
        AstNode* child=parsePortList();
        if(child!=nullptr){
            node->children.push_back(child);
        }
        if(currentToken.type==SEPARATOR&&currentToken.value==";"){
            currentToken=tokens[++currentTokenIndex];
        }
        AstNode* child2=parseStatement();
        if(child2!=nullptr){
            node->children.push_back(child2);
        }
        return node;
    }else{
        std::cout<<"Error: Expected module declaration"<<std::endl;
        return nullptr;
    }
}

AstNode* Parser::parsePortList(){
    if(currentToken.type==BRACKET&&currentToken.value=="("){
        currentToken=tokens[++currentTokenIndex];
        AstNode* node=new AstNode();
        node->value="port_list";
        node->type="port_list";
        while(currentToken.type!=BRACKET&&currentToken.value!=")"){
            AstNode* child=new AstNode();
            child->value="port";
            child->type="port";
            child->value+=currentToken.value;
            node->children.push_back(child);
            currentToken=tokens[++currentTokenIndex];
            if(currentToken.type==SEPARATOR&&currentToken.value==","){
                currentToken=tokens[++currentTokenIndex];
            }
        }
        if(currentToken.type==BRACKET&&currentToken.value==")"){
            currentToken=tokens[++currentTokenIndex];
        }
        return node;
    }else{
        std::cout<<"Error: Expected port list"<<std::endl;
        return nullptr;
    }
     
}


AstNode* Parser::parseStatement(){
    if(currentToken.type==KEYWORD){
        if(currentToken.value=="if"){
            return parseIfStatement();
        }else if(currentToken.value=="assign"){
            return parseAssignment();
        }else if(currentToken.value=="initial"){
            return parseInitialStatement();
        }else if(currentToken.value=="always"){
            return parseAlwaysStatement();
        }else{
            std::cerr<<"Error: unknown keyword "<<currentToken.value<<std::endl;
            exit(1);
        }
    }
}

AstNode* Parser::parseIfStatement(){
    AstNode* node=new AstNode();
    node->value="if";
    node->type="if";
    currentToken=tokens[++currentTokenIndex];
    if(currentToken.type==BRACKET&&currentToken.value=="("){
        currentToken=tokens[++currentTokenIndex];
        AstNode* child=parseExpression();
        if(child!=nullptr){
            node->children.push_back(child);
        }
        if(currentToken.type==BRACKET&&currentToken.value==")"){
            currentToken=tokens[++currentTokenIndex];
        }else{
            std::cerr<<"Error: Expected ) after if expression"<<std::endl;
            exit(1);
        }
        AstNode* child2=parseStatement();
        if(child2!=nullptr){
            node->children.push_back(child2);
        }
        if(currentToken.type==KEYWORD&&currentToken.value=="else"){
            currentToken=tokens[++currentTokenIndex];
            AstNode* child3=parseStatement();
            if(child3!=nullptr){
                node->children.push_back(child3);
            }
        }
        return node;
    }else{
        std::cerr<<"Error: Expected ( after if"<<std::endl;
        exit(1);
    }
}

AstNode* Parser::parseAssignment(){
    AstNode* node=new AstNode();
    node->value="assign";
    node->type="assign";
    currentToken=tokens[++currentTokenIndex];
    if(currentToken.type==IDENTIFIER){
        AstNode* child=new AstNode();
        child->value=currentToken.value;
        child->type="variable";
        node->children.push_back(child);
        currentToken=tokens[++currentTokenIndex];
    }
    if(currentToken.type==OPERATOR&&currentToken.value=="="){
        currentToken=tokens[++currentTokenIndex];
    }else{
        std::cerr<<"Error: Expected = in assignment"<<std::endl;
        exit(1);
    }
    AstNode* child2=parseExpression();
    if(child2!=nullptr){
        node->children.push_back(child2);
    }
    if(currentToken.type==SEPARATOR&&currentToken.value==";"){
        currentToken=tokens[++currentTokenIndex];
    }else{
        std::cerr<<"Error: Expected ; after assignment"<<std::endl;
        exit(1);
    }
    return node;
}

AstNode* Parser::parseAlwaysStatement(){
    AstNode* node=new AstNode();
    node->value="always";
    node->type="always";
    currentToken=tokens[++currentTokenIndex];
    if(currentToken.type==OPERATOR&&currentToken.value=="@"){
        currentToken=tokens[++currentTokenIndex];
    }else{
        std::cerr<<"Error: Expected @ in always statement"<<std::endl;
        exit(1);
    }
    if(currentToken.type==BRACKET&&currentToken.value=="("){
        currentToken=tokens[++currentTokenIndex];
        while(currentToken.type!=BRACKET&&currentToken.value!=")"){
            AstNode* child=new AstNode();
            child->value=currentToken.value;
            child->type="variable";
            node->children.push_back(child);
            currentToken=tokens[++currentTokenIndex];
            if(currentToken.type==SEPARATOR&&currentToken.value==","){
                currentToken=tokens[++currentTokenIndex];
            }
        }
        currentToken=tokens[++currentTokenIndex];
        AstNode* child2=parseStatement();
        if(child2!=nullptr){
            node->children.push_back(child2);
        }
        return node;
    }
}

AstNode* Parser::parseInitialStatement(){
    AstNode* node=new AstNode();
    node->value="initial";
    node->type="initial";
    currentToken=tokens[++currentTokenIndex];
    AstNode* child=parseStatement();
    if(child!=nullptr){
        node->children.push_back(child);
    }
    return node;
}


AstNode* Parser::parseExpression(int level){
    Token nextToken;
    if(currentTokenIndex+1<tokens.size()){nextToken=tokens[currentTokenIndex+1];}
    if(currentToken.type==OPERATOR){//unary expression
        return parseUnaryExpression();
    }else if(currentTokenIndex+1<tokens.size()&&nextToken.type==OPERATOR&&level==0){//binary expression
        return parseBinaryExpression();
    }else if(currentToken.type==IDENTIFIER){
        AstNode* node=new AstNode();
        node->value=currentToken.value;
        node->type="variable";
        currentToken=tokens[++currentTokenIndex];
        return node;
    }else if(currentToken.type==NUMBER){
        AstNode* node=new AstNode();
        node->value=currentToken.value;
        node->type="number";
        currentToken=tokens[++currentTokenIndex];
        return node;
    }else{
        std::cerr<<"Error: Expected expression"<<std::endl;
        exit(1);
    }
    return nullptr;
}

AstNode* Parser::parseUnaryExpression(){
    AstNode* node=new AstNode();
    node->value=currentToken.value;
    node->type="operator";
    currentToken=tokens[++currentTokenIndex];
    AstNode* child=parseExpression();
    if(child!=nullptr){
        node->children.push_back(child);
    }
    return node;
}

AstNode* Parser::parseBinaryExpression(){
    AstNode* node=parseExpression(1);
    if(currentToken.type==OPERATOR){
        AstNode* op=new AstNode();
        op->value=currentToken.value;
        op->type="operator";
        currentToken=tokens[++currentTokenIndex];
        AstNode* child2=parseExpression(1);
        if(child2!=nullptr){
            op->children.push_back(node);
            op->children.push_back(child2);
            return op;
        }
    }
}