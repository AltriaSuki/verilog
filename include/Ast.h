#include<iostream>
#include<string>
#include<vector>
#include"Token.h"

class AstNode{
    public:
        std::string value;
        std::string type;
        std::vector<AstNode*> children;
    public:
        void print(int depth){
            for(int i=0;i<depth;++i){
                std::cout<<"--";
            }
            std::cout<<value<<std::endl;
            for(auto child:children){
                child->print(depth+1);
            }
        }
};