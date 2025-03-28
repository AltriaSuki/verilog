#include"RTLILGen.h"
#include<string>
#include"helper.h"


std::string RTLILGen::generateRTLIL(){
    for(auto module:root->children){
        result+= "module \\"+module->value+"\n";
        //生成端口列表
        generatePortList(module);
        //生成模块体
        generateModuleBody(module);
        result+="endmodule\n";
    }
    return result;
}

void RTLILGen::generatePortList(AstNode* node){//默认最后一个端口是输出端口
    node=node->children[0];//获取端口列表
    int size=node->children.size();
    if(node->children[size-1]==nullptr){
        size--;
    }
    for(int i=0;i<size-1;++i){
        AstNode* port=node->children[i];
        result+="input width 1 \\"+port->value+"\n";
        portList.insert(port->value);
    }
    AstNode* lastPort=node->children[size-1];
    result+="output width 1 \\"+lastPort->value+"\n";
    portList.insert(lastPort->value);
}

void RTLILGen::generateModuleBody(AstNode* node){
    for(auto body:node->children){
        if(body->type=="declaration"){
            generateDeclaration(body);
        }else if(body->type=="statement"){
            generateStatement(body);
        }
    }
}

void RTLILGen::generateDeclaration(AstNode* node){
    if(node->value=="input"){
        AstNode* var=node->children[0];
        if(portList.find(var->value)==portList.end()){
            result+="wire input width 1 \\"+var->value+"\n";
            portList.insert(var->value);
        }else{
            std::cerr<<"Error: duplicate port "<<var->value<<std::endl;
            exit(1);
        }
    }else if(node->value=="output"){
        AstNode* var=node->children[0];
        if(portList.find(var->value)==portList.end()){
            result+="wire output width 1 \\"+var->value+"\n";
            portList.insert(var->value);
        }else{
            std::cerr<<"Error: duplicate port "<<var->value<<std::endl;
            exit(1);
        }
    }else if(node->value=="reg"){
        AstNode* var=node->children[0];
        if(portList.find(var->value)==portList.end()){
            result+="reg width 1 \\"+var->value+"\n";
            portList.insert(var->value);
        }else{
            std::cerr<<"Error: duplicate port "<<var->value<<std::endl;
            exit(1);
        }
    }else if(node->value=="wire"){
        AstNode* var=node->children[0];
        if(portList.find(var->value)==portList.end()){
            result+="wire width 1 \\"+var->value+"\n";
            portList.insert(var->value);
        }else{
            std::cerr<<"Error: duplicate port "<<var->value<<std::endl;
            exit(1);
        }
    }else if(node->value=="integer"){
        AstNode* var=node->children[0];
        if(portList.find(var->value)==portList.end()){
            result+="wire width 32 \\"+var->value+"\n";
            portList.insert(var->value);
        }else{
            std::cerr<<"Error: duplicate port "<<var->value<<std::endl;
            exit(1);
        }
    }else{
        std::cerr<<"Error: unknown declaration type "<<node->value<<std::endl;
        exit(1);
    }
}

void RTLILGen::generateStatement(AstNode* node){
    if(node->value=="assign"){
        generateAssignment(node);
    }else if(node->value=="if"){
        generateIfStatement(node);
    }else if(node->value=="always"){
        generateAlwaysStatement(node);
    }else if(node->value=="initial"){
        generateInitialStatement(node);
    }
    else{
        std::cerr<<"Error: unknown statement type "<<node->type<<std::endl;
        exit(1);
    }
}

void RTLILGen::generateAssignment(AstNode* node){//只能处理简单的赋值语句，如assign a=b+c;而不支持assign a=b+c+d;
    std::string op=node->children[1]->value;
    AstNode* op_node=node->children[1];
    result+="cell $"+to_operator_string(op)+" (\n";
    result+=".A("+op_node->children[0]->value+"),\n";
    result+=".B("+op_node->children[1]->value+"),\n";
    result+=".Y("+node->children[0]->value+"),\n";
    result+=");\n";
}

void RTLILGen::generateIfStatement(AstNode* node){

}
void RTLILGen::generateElseStatement(AstNode* node){

}
void RTLILGen::generateAlwaysStatement(AstNode* node){

}
void RTLILGen::generateInitialStatement(AstNode* node){

}
void RTLILGen::generateExpression(AstNode* node){

}
void RTLILGen::generateBinaryExpression(AstNode* node){

}
void RTLILGen::generateUnaryExpression(AstNode* node){

}
