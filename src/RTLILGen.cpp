#include"RTLILGen.h"
#include<string>
#include<set>
#include<vector>
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

int RTLILGen::incre_num(std::string op){
    if(op=="add"){
        return ++add_num;
    }else if(op=="sub"){
        return ++sub_num;
    }else if(op=="mul"){
        return ++mul_num;
    }else if(op=="div"){
        return ++div_num;
    }else if(op=="mod"){
        return ++mod_num;
    }else if(op=="and"){
        return ++and_num;
    }else if(op=="or"){
        return ++or_num;
    }else if(op=="xor"){
        return ++xor_num;
    }else if(op=="not"){
        return ++not_num;
    }else if(op=="eq"){
        return ++eq_num;
    }else if(op=="ne"){
        return ++ne_num;
    }else if(op=="lt"){
        return ++lt_num;
    }else if(op=="le"){
        return ++le_num;
    }else if(op=="gt"){
        return ++gt_num;
    }else if(op=="ge"){
        return ++ge_num;
    }
    return 0;
}
void RTLILGen::assign_helper(AstNode* node){
    if(node->children.size()==0){//叶子节点
        return;
    }
    assign_helper(node->children[0]);
    assign_helper(node->children[1]);
    
    result+="cell $"+to_operator_string(node->value)
    +"$ "+to_operator_string(node->value)+"$"
    +std::to_string(incre_num(to_operator_string(node->value)))+"\n";
    if(node->children[0]->type=="variable"){
        result+="connect \\A \\"+node->children[0]->value+"\n";
    }else if(node->children[0]->type=="number"){
        result+="connect \\A \\"+node->children[0]->value+"\n";
    }else{
        if(node->children[1]->type=="operator"){
            result+="connect \\A \\tmp"+std::to_string(temp_id-1)+"\n";
        }else{
            result+="connect \\A \\tmp"+std::to_string(temp_id)+"\n";
        }
        
    }
    if(node->children[1]->type=="variable"){
        result+="connect \\B \\"+node->children[1]->value+"\n";
    }else if (node->children[1]->type=="number")
    {
        result+="connect \\B \\"+node->children[1]->value+"\n";
    }else {
        result+="connect \\B \\tmp"+std::to_string(temp_id)+"\n";
    }
    result+="connect \\Y \\"+new_temp()+"\n";
    result+="end\n";
}
void RTLILGen::generateAssignment(AstNode* node){
    if(node->children[1]->children.size()==0){
        result+="connect \\"+node->children[0]->value+" \\"+node->children[1]->value+"\n";
        result+="end\n";
        return;
    }
    std::string lhs=node->children[0]->value;
    std::string op=node->children[1]->value;
    std::vector<AstNode*> op_type;
    temp_id=0;
    
    assign_helper(node->children[1]);
    result+="connect \\"+lhs+"\\tmp"+std::to_string(temp_id)+"\n";
    result+="end\n";

}
//最多有三个子结点；有两个子结点时，没有else；有三个子结点时，有else
void RTLILGen::generateIfStatement(AstNode* node){//现在的if语句只支持assign statement
    int len=node->children.size();
    if(len<2){
        std::cerr<<"Error: if statement should have at least 2 children"<<std::endl;
        exit(1);
    }else if(len==2){
        temp_id=0;//重置temp_id,使得每个if语句的临时变量不冲突
        AstNode* condition=node->children[0];
        AstNode* statement=node->children[1];
        if(condition->type=="operator"){
            result+="cell $"+to_operator_string(condition->value)+"$ "
            +to_operator_string(condition->value)+"$"+std::to_string(incre_num(to_operator_string(condition->value)))+"\n";
            result+="connect \\A \\"+condition->children[0]->value+"\n";
            result+="connect \\B \\"+condition->children[1]->value+"\n";
            result+="connect \\Y \\cond\n";//这里的id必定是1
            result+="end\n";
        }else{
            result+="connect \\"+condition->value+" \\cond\n";
            result+="end\n";
        }
        if(statement->children[1]->children.size()==0){
            result+="connect \\"+new_temp()+" \\"+statement->children[1]->value+"\n";
            result+="end\n";
        }else{
            assign_helper(statement->children[1]);
        }
        

        result+="cell $mux$ mux$"+std::to_string(++mul_num)+"\n";
        result+="connect \\A \\a\n";
        result+="connect \\B \\tmp"+std::to_string(temp_id)+"\n";
        result+="connect \\S \\cond\n";
        result+="connect \\Y \\a\n";
        result+="end\n";
    }else if(len==3){
        if(node->children[2]->value!="if"){//这就表示只有一层else语句
            temp_id=0;
            AstNode* condition=node->children[0];
            AstNode* statement=node->children[1];
            AstNode* else_statement=node->children[2];
            if(condition->type=="operator"){
                result+="cell $"+to_operator_string(condition->value)+"$ "
                +to_operator_string(condition->value)+"$"+std::to_string(incre_num(to_operator_string(condition->value)))+"\n";
                result+="connect \\A \\"+condition->children[0]->value+"\n";
                result+="connect \\B \\"+condition->children[1]->value+"\n";
                result+="connect \\Y \\cond\n";//这里的id必定是1
                result+="end\n";
            }else{
                result+="connect \\"+condition->value+" \\cond\n";
                result+="end\n";
            }

            if(statement->children[1]->children.size()==0){
                result+="connect \\"+new_temp()+" \\"+statement->children[1]->value+"\n";
                result+="end\n";
            }else{
                assign_helper(statement->children[1]);
            }

            if(else_statement->children[1]->children.size()==0){
                result+="connect \\"+new_temp()+" \\"+else_statement->children[1]->value+"\n";
                result+="end\n";
            }else{
                assign_helper(else_statement->children[1]);
            }

            result+="cell $mux$ mux$"+std::to_string(++mul_num)+"\n";
            result+="connect \\A \\tmp"+std::to_string(temp_id)+"\n";
            result+="connect \\B \\tmp"+std::to_string(temp_id-1)+"\n";
            result+="connect \\S \\cond\n";
            result+="connect \\Y \\a\n";
            result+="end\n";

        }else{//表示有多层else语句;递归调用
            
        }
    }

}
void RTLILGen::generateElseStatement(AstNode* node){

}
void RTLILGen::generateAlwaysStatement(AstNode* node){

}
void RTLILGen::generateInitialStatement(AstNode* node){

}
