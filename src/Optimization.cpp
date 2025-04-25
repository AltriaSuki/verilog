#include"Optimization.h"


AstNode* Optimization::constant_folding(AstNode* nodes){
    if(nodes==nullptr) return nullptr;
    for(auto & node:nodes->children){
        node=constant_folding(node);
    }
    if(nodes->type=="operator"){
        if(nodes->children[0]->type=="number"&&nodes->children[1]->type=="number"){
            int num1=std::stoi(nodes->children[0]->value);
            int num2=std::stoi(nodes->children[1]->value);
            int result;
            if(nodes->value=="+"){
                result=num1+num2;
            }else if(nodes->value=="-"){
                result=num1-num2;
            }else if(nodes->value=="*"){
                result=num1*num2;
            }else if(nodes->value=="/"){
                if(num2==0){
                    std::cerr<<"Error: division by zero"<<std::endl;
                    exit(1);
                }
                result=num1/num2;
            }else if(nodes->value=="%"){
                if(num2==0){
                    std::cerr<<"Error: division by zero"<<std::endl;
                    exit(1);
                }
                result=num1%num2;
            }else if(nodes->value=="=="){
                result=num1==num2;
            }else if(nodes->value=="!="){
                result=num1!=num2;
            }else if(nodes->value=="<"){
                result=num1<num2;
            }else if(nodes->value==">"){
                result=num1>num2;
            }else if(nodes->value=="<="){
                result=num1<=num2;
            }else if(nodes->value==">="){
                result=num1>=num2;
            }else if(nodes->value=="&&"){
                result=num1&&num2;
            }else if(nodes->value=="||"){
                result=num1||num2;
            }

            nodes->type="number";
            nodes->value=std::to_string(result);
            nodes->children.clear();

        }
    }
    return nodes;
}