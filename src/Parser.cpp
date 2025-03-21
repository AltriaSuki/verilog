#include"../include/Parser.h"
#include"../include/Token.h"

Parser::Parser(Lexer& lexer){
    //获取一组tokens
    Token token=lexer.NextToken();
    while(token.type!=END_OF_INPUT){
        tokens.push_back(token);
        token=lexer.NextToken();
    }
    tokens.push_back(token);//push back the END_OF_INPUT token
    currentTokenIndex=0;
    currentToken=tokens[currentTokenIndex++];
}

AstNode* Parser::parseProgram(){
    AstNode* node=new AstNode();
    node->value="program";
    while(currentToken.value!="endmodule") {
        AstNode* child=parseModuleDeclaration();
        if(child!=nullptr){
            node->children.push_back(child);
        }
    }
    return node;
}

AstNode* Parser::parseModuleDeclaration(){
    //输入错误处理，传入空节点
    if (currentToken.type != TokenType::KEYWORD || currentToken.value != "module")
    {
        std::cout << "wrrong input:it is not module"<<std::endl;
        return nullptr;
    }
    //读取下一个token
    currentToken = tokens[currentTokenIndex++];
    if (currentToken.type != TokenType::IDENTIFIER)
    {
        std::cout << "wrrong input:it is not a right moudule name" << std::endl;
        return nullptr;
    }
    //该节点是Moudle
    AstNode* node = new AstNode();
    node->value = currentToken.value;

    //以上处理了MOUDLE关键字和moudle名

    //处理参数列表
    //子节点参数列表,参数列表在子节点并排表示
    node->children.push_back(parsePortList());
    //ct=";"
    currentToken = tokens[currentTokenIndex++];

    //子节点模块体
    while (currentToken.value != "endmodule")
    {
        node->children.push_back(parseModuleBody());
       
    }
    

    return node;
}

//TODO
AstNode* Parser::parseModuleBody()
{
    //获取模块体的每一行第一个
    currentToken= tokens[currentTokenIndex++];
    AstNode* node = new AstNode();
    node->value = "statement";
    if (currentToken.type != TokenType::KEYWORD)
    {
        std::cout << "空语句" << std::endl;
        return node;
    }
   //声明模块
    if ( currentToken.value == "input"|| currentToken.value == "reg"|| currentToken.value == "output"|| currentToken.value == "integer"|| currentToken.value == "wire")
    {
        node=parseDeclaration();
    }


    else {
        node=parseStatement();
    }

    return node;
}

/*
声明语句
*/
AstNode* Parser::parseDeclaration()
{
    AstNode* node = new AstNode();
    if (currentToken.type == TokenType::KEYWORD)
    {
        node->value = currentToken.value;
        //获取声明变量
        currentToken = tokens[currentTokenIndex++];
        
        while (currentToken.value != ";")
        {
            //跳过逗号
            if (currentToken.value == ",")
            {
                currentToken = tokens[currentTokenIndex++];
            }

            AstNode* parm = new AstNode();
            parm->value = currentToken.value;
            node->children.push_back(parm);
            currentToken = tokens[currentTokenIndex++];
        }
    }
    return node;


}

//参数列表
AstNode* Parser::parsePortList()
{
    currentToken = tokens[currentTokenIndex++];
    if (currentToken.value != "(")
    {
        std::cout << "wrong input" << std::endl;
        return nullptr;
    }
    AstNode* node = new AstNode();
    node->value = "parsePortList";
    currentToken = tokens[currentTokenIndex++];
    //记得在树节点手动释放内存，该代码没有使用智能指针
    AstNode* childnode = new AstNode();
    childnode->value = currentToken.value;
    node->children.push_back(childnode);

    //调用下一级，参数在子节点并排表示
    while(currentToken.value!=")")
    node->children.push_back(parsePortListTail());
    
     return node;

}


AstNode* Parser::parsePortListTail()
{
    //cT=","
    currentToken = tokens[currentTokenIndex++];
    //如果不是逗号,退出
    if (currentToken.value != ",")
    {
        return nullptr;
    }
    //ct="参数"
    currentToken = tokens[currentTokenIndex++];

    AstNode* node = new AstNode();
    node->value = currentToken.value;
    return node;

}



AstNode* Parser::parseAssignment() {
    AstNode* node = new AstNode();
    node->value = "assign";
    node->type = "assign";
    currentToken = tokens[++currentTokenIndex];
    if (currentToken.type == IDENTIFIER) {
        AstNode* child = new AstNode();
        child->value = currentToken.value;
        child->type = "variable";
        node->children.push_back(child);
        currentToken = tokens[++currentTokenIndex];
    }
    if (currentToken.type == OPERATOR && currentToken.value == "=") {
        currentToken = tokens[++currentTokenIndex];
    }
    else {
        std::cerr << "Error: Expected = in assignment" << std::endl;
        exit(1);
    }
    AstNode* child2 = parseExpression();
    if (child2 != nullptr) {
        node->children.push_back(child2);
    }
    if (currentToken.type == SEPARATOR && currentToken.value == ";") {
        currentToken = tokens[++currentTokenIndex];
    }
    else {
        std::cerr << "Error: Expected ; after assignment" << std::endl;
        exit(1);
    }
    return node;
}

AstNode* Parser::parseAlwaysStatement() {
    AstNode* node = new AstNode();
    node->value = "always";
    node->type = "always";
    currentToken = tokens[++currentTokenIndex];
    if (currentToken.type == OPERATOR && currentToken.value == "@") {
        currentToken = tokens[++currentTokenIndex];
    }
    else {
        std::cerr << "Error: Expected @ in always statement" << std::endl;
        exit(1);
    }
    if (currentToken.type == BRACKET && currentToken.value == "(") {
        currentToken = tokens[++currentTokenIndex];
        while (currentToken.type != BRACKET && currentToken.value != ")") {
            AstNode* child = new AstNode();
            child->value = currentToken.value;
            child->type = "variable";
            node->children.push_back(child);
            currentToken = tokens[++currentTokenIndex];
            if (currentToken.type == SEPARATOR && currentToken.value == ",") {
                currentToken = tokens[++currentTokenIndex];
            }
        }
        currentToken = tokens[++currentTokenIndex];
        AstNode* child2 = parseStatement();
        if (child2 != nullptr) {
            node->children.push_back(child2);
        }
        return node;
    }
}

AstNode* Parser::parseInitialStatement() {
    AstNode* node = new AstNode();
    node->value = "initial";
    node->type = "initial";
    currentToken = tokens[++currentTokenIndex];
    AstNode* child = parseStatement();
    if (child != nullptr) {
        node->children.push_back(child);
    }
    return node;
}


AstNode* Parser::parseExpression(int level) {
    Token nextToken;
    if (currentTokenIndex + 1 < tokens.size()) { nextToken = tokens[currentTokenIndex + 1]; }
    if (currentToken.type == OPERATOR) {//unary expression
        return parseUnaryExpression();
    }
    else if (currentTokenIndex + 1 < tokens.size() && nextToken.type == OPERATOR && level == 0) {//binary expression
        return parseBinaryExpression();
    }
    else if (currentToken.type == IDENTIFIER) {
        AstNode* node = new AstNode();
        node->value = currentToken.value;
        node->type = "variable";
        currentToken = tokens[++currentTokenIndex];
        return node;
    }
    else if (currentToken.type == NUMBER) {
        AstNode* node = new AstNode();
        node->value = currentToken.value;
        node->type = "number";
        currentToken = tokens[++currentTokenIndex];
        return node;
    }
    else {
        std::cerr << "Error: Expected expression" << std::endl;
        exit(1);
    }
    return nullptr;
}

AstNode* Parser::parseUnaryExpression() {
    AstNode* node = new AstNode();
    node->value = currentToken.value;
    node->type = "operator";
    currentToken = tokens[++currentTokenIndex];
    AstNode* child = parseExpression();
    if (child != nullptr) {
        node->children.push_back(child);
    }
    return node;
}

AstNode* Parser::parseBinaryExpression() {
    AstNode* node = parseExpression(1);
    if (currentToken.type == OPERATOR) {
        AstNode* op = new AstNode();
        op->value = currentToken.value;
        op->type = "operator";
        currentToken = tokens[++currentTokenIndex];
        AstNode* child2 = parseExpression(1);
        if (child2 != nullptr) {
            op->children.push_back(node);
            op->children.push_back(child2);
            return op;
        }
    }
}
AstNode* Parser::parseStatement() {
    if (currentToken.type == KEYWORD) {
        if (currentToken.value == "if") {
            return parseIfStatement();
        }
        else if (currentToken.value == "assign") {
            return parseAssignment();
        }
        else if (currentToken.value == "initial") {
            return parseInitialStatement();
        }
        else if (currentToken.value == "always") {
            return parseAlwaysStatement();
        }
        else {
            std::cerr << "Error: unknown keyword " << currentToken.value << std::endl;
            exit(1);
        }
    }
}
AstNode* Parser::parseIfStatement() {
    AstNode* node = new AstNode();
    node->value = "if";
    node->type = "if";
    currentToken = tokens[++currentTokenIndex];
    if (currentToken.type == BRACKET && currentToken.value == "(") {
        currentToken = tokens[++currentTokenIndex];
        AstNode* child = parseExpression();
        if (child != nullptr) {
            node->children.push_back(child);
        }
        if (currentToken.type == BRACKET && currentToken.value == ")") {
            currentToken = tokens[++currentTokenIndex];
        }
        else {
            std::cerr << "Error: Expected ) after if expression" << std::endl;
            exit(1);
        }
        AstNode* child2 = parseStatement();
        if (child2 != nullptr) {
            node->children.push_back(child2);
        }
        if (currentToken.type == KEYWORD && currentToken.value == "else") {
            currentToken = tokens[++currentTokenIndex];
            AstNode* child3 = parseStatement();
            if (child3 != nullptr) {
                node->children.push_back(child3);
            }
        }
        return node;
    }
    else {
        std::cerr << "Error: Expected ( after if" << std::endl;
        exit(1);
    }
}