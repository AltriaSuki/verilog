#include<iostream>
#include<string>
#include<vector>
#include"Token.h"

class AstNode{
    public:
        Token token;
        std::vector<AstNode*> children;
    public:
        void print(int depth){
            for(int i=0;i<depth;++i){
                std::cout<<"--";
            }
            token.print();
            for(auto child:children){
                child->print(depth+1);
            }
        }
};