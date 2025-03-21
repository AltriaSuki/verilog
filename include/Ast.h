#include<iostream>
#include<string>
#include<vector>
#include"Token.h"

class AstNode{
    public:
        std::string value;
        std::vector<AstNode*> children;
        std::string type;
    public:
        void print(int depth){
            for(int i=0;i<depth;++i){
                std::cout<<"--";
            }
            std::cout<<value<<std::endl;
            for(auto child:children){
                if (child == nullptr)
                {
                    continue;
                }

                child->print(depth+1);
            }
        }
};