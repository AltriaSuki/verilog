#include<iostream>
#include<string>
#include<vector>
#include"Token.h"
#pragma once

class AstNode{
    public:
        std::string value;
        std::vector<AstNode*> children;
        std::string type;
    private:
        void destory(AstNode* node){
            for(auto child:node->children){
                if(child == nullptr){
                    continue;
                }
                destory(child);
            }
            delete node;
        }
    public:
        ~AstNode(){
            destory(this);
        }
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