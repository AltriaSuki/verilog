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

void Optimization::optimize_in_Ast(){
    root=constant_folding(root);
}

void Optimization::set_rtlil_code(std::string rtlil){
    rtlil_code=rtlil;
    divide_into_blocks();
}

void Optimization::divide_into_blocks(){
    std::string block;
    std::string line;
    std::istringstream stream(rtlil_code);
    bool in_cell=false;
    while(getline(stream,line)){
        if(line.find("cell")!=std::string::npos){
            in_cell=true;
            block+=line+"\n";
        }else if(in_cell&&line.find("end")!=std::string::npos){
            //此时已经结束了一个cell
            //将block中的信息提取出来
            //并存储到blocks中
            in_cell=false;
            block+=line+"\n";
            info block_info;
            block_info.in_cell=true;
            std::string _line;
            std::istringstream line_stream(block);
            int count=0;
            while(getline(line_stream,_line)){
                count++;
                std::istringstream _line_stream(_line);
                std::string token;
                while(_line_stream>>token);//直接读取到最后一个token
                auto pos=token.find("$");
                switch(count){
                    case 1:
                        block_info.cell_name=token;
                        if(pos!=std::string::npos){
                            block_info.cell_type=token.substr(0,pos);
                        }
                        break;
                    case 2:
                        block_info.A=token;
                        break;
                    case 3:
                        block_info.B=token;
                        break;
                    case 4:
                        block_info.Y=token;
                        break;
                    case 5:
                        block_info.S=token;
                        break;

                }
            }
            auto info=new whole_info;
            info->whole_info=block;
            info->block_info=block_info;
            info->is_opration=true;
            whole_blocks.push_back(info);
            block="";

        }else if(in_cell){
            block+=line+"\n";
        }else if(line.find("connect")!=std::string::npos){
            //此处处理connect语句
            //connect的右边是input，左边是output
            //例如 connect \m \a,即为将a赋值给m
            block+=line+"\n";
            std::string token;
            std::istringstream line_stream(line);
            info block_info;
            block_info.in_cell=false;
            block_info.cell_name="connect";
            block_info.cell_type="connect";
            int count=0;
            while(line_stream>>token){
                count++;
                if(count==3){
                    block_info.input=token;
                }else if(count==2){
                    block_info.output=token;
                }
            }
            auto info=new whole_info;
            info->whole_info=block;
            info->block_info=block_info;
            info->is_opration=true;
            whole_blocks.push_back(info);
            block="";
        }else{
            block+=line+"\n";
            auto info=new whole_info;
            info->whole_info=block;
            info->block_info.in_cell=false;
            info->is_opration=false;
            whole_blocks.push_back(info);
            block="";
        }
    }
}

void Optimization::common_subexpression_elimination(){
    for(size_t i=0;i<whole_blocks.size();i++){
        if(!whole_blocks[i]->is_opration)continue;
        for(int j=i+1;j<whole_blocks.size();j++){
            if(!whole_blocks[j]->is_opration)continue;
            if(whole_blocks[i]->block_info.A==whole_blocks[j]->block_info.Y)
                break;//表明a的值已经改变了
            if(whole_blocks[i]->block_info.B==whole_blocks[j]->block_info.Y)
                break;//表明b的值已经改变了
            //下面是对cell的操作
            //不对if语句进行优化
            if(whole_blocks[i]->block_info.cell_type==whole_blocks[j]->block_info.cell_type){
                if(whole_blocks[i]->block_info.A==whole_blocks[j]->block_info.A&&
                   whole_blocks[i]->block_info.B==whole_blocks[j]->block_info.B){
                    std::string Y1=whole_blocks[i]->block_info.Y;
                    std::string Y2=whole_blocks[j]->block_info.Y;
                    std::string block="connect "+Y2+" "+Y1+"\n";
                    whole_blocks[j]->whole_info=block;
                    whole_blocks[j]->block_info.in_cell=false;
                    whole_blocks[j]->block_info.cell_name="connect";
                    whole_blocks[j]->block_info.cell_type="connect";
                    whole_blocks[j]->block_info.input=Y1;
                    whole_blocks[j]->block_info.output=Y2;
                   }
            }
        }
    }
}

void Optimization::optimize_in_rtlil(){
    common_subexpression_elimination();
}

std::string Optimization::get_optimized_rtlil(){
    std::string result;
    for(auto block:whole_blocks){
        result+=block->whole_info;
    }
    __cplusplus;
    return result;
}