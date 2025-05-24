#include "solver.h"

void solver::read_file(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr<<"Error opening file: "<<filename<<std::endl;
        return;
    }
    std::string line;
    while(std::getline(file,line)){
        //这里的min里面只有加法
        if(line.find("Min")!=std::string::npos){
            std::getline(file,line);
            std::istringstream iss(line);
            std::string token;
            while(iss>>token){
                if(token.length()==3){
                    auto binary_ptr=std::make_unique<binary>();
                    binary_ptr->name=token;
                    binary_ptr->coefficient=1;
                    min_collection.insert(std::move(binary_ptr));
                }else if(token.length()>3){
                    auto binary_ptr=std::make_unique<binary>();
                    binary_ptr->name=token.substr(1);
                    binary_ptr->coefficient=std::stoi(token.substr(0,1));
                    min_collection.insert(std::move(binary_ptr));
                }
            }
        }else if(line.find("subject to")!=std::string::npos){
            size_t count=0;
            while(getline(file,line)){
                if(line.find("binary")!=std::string::npos){
                    break;
                }else if(line.find("unique")!=std::string::npos){
                    continue;
                }else if(line.find("sequence")!=std::string::npos){
                    continue;
                }else if(line.find("resource")!=std::string::npos){
                    continue;
                }else{
                    std::istringstream iss(line);
                    std::string token;
                    size_t pos=0;
                    bool positive=true;
                    auto constraint_ptr=std::make_unique<constraint>();
                    constraint_ptr->index=count++;
                    while(iss>>token){
                        if(pos==0){//pos为0时必定为正数
                            auto binary_ptr=std::make_unique<binary>();
                            if(token.length()==3){
                                binary_ptr->name=token;
                                binary_ptr->coefficient=1;
                            }else{
                                binary_ptr->name=token.substr(1);
                                binary_ptr->coefficient=std::stoi(token.substr(0,1));
                            }
                            pos++;
                            constraint_ptr->binary_collection.insert(std::move(binary_ptr));
                        }else if(token.find("+")!=std::string::npos){
                            positive=true;
                        }else if(token.find("-")!=std::string::npos){
                            positive=false;
                        }else if(token.find("<=")!=std::string::npos){
                            constraint_ptr->type="<=";
                            iss>>token;
                            constraint_ptr->value=std::stoi(token);
                        }else if(token.find(">=")!=std::string::npos){
                            constraint_ptr->type=">=";
                            iss>>token;
                            constraint_ptr->value=std::stoi(token);
                        }else if(token.find("=")!=std::string::npos){
                            constraint_ptr->type="=";
                            iss>>token;
                            constraint_ptr->value=std::stoi(token);
                        }else{
                            auto binary_ptr=std::make_unique<binary>();
                            if(token.length()==3){
                                binary_ptr->name=token;
                                binary_ptr->coefficient=1;
                            }else{
                                binary_ptr->name=token.substr(1);
                                binary_ptr->coefficient=std::stoi(token.substr(0,1));
                            }
                            if(!positive){
                                binary_ptr->coefficient*=-1;
                            }
                            constraint_ptr->binary_collection.insert(std::move(binary_ptr));
                        }
                    }
                    constraints_collection.insert(std::move(constraint_ptr));
                }
            }
        } 
        //确保我读取到了binary后直接能够跳出循环并且还能够判断
        if(line.find("binary")!=std::string::npos){
            size_t count=0;
            while(getline(file,line)){
                if(line.find("end")!=std::string::npos){
                    break;
                }else{
                    var_index[line]=++count;//确保变量的索引从1开始
                    index_var[count]=line;
                }
            }
        }
    }
}

void solver::glpk_solver(){
    glp_prob* lp=glp_create_prob();
    glp_set_prob_name(lp,"ILP");
    glp_set_obj_dir(lp,GLP_MIN);

    //添加binary变量
    size_t n=var_index.size();
    size_t num_of_obj=min_collection.size();
    glp_add_cols(lp,n);

    //添加binary变量
    for(size_t i=0;i<n;++i){
        auto it=var_index.begin();
        std::advance(it,i);
        int index=(*it).second;
        glp_set_col_name(lp,index,(*it).first.c_str());
        glp_set_col_bnds(lp,index,GLP_DB,0.0,1.0);
        glp_set_col_kind(lp,index,GLP_BV);
        glp_set_obj_coef(lp,index,0.0);
    }

    for(size_t i=0;i<num_of_obj;++i){
        auto it=min_collection.begin();
        std::advance(it,i);
        int index=var_index[(*it)->name];
        glp_set_obj_coef(lp,index,(*it)->coefficient);
    }

    //添加约束
    size_t m=constraints_collection.size();
    glp_add_rows(lp,m);
    constexpr double INF=1e9;
    for(size_t i=0;i<m;++i){
        auto it=constraints_collection.begin();
        std::advance(it,i);
        glp_set_row_name(lp,i+1,(*it)->type.c_str());
        if((*it)->type=="="){
            glp_set_row_bnds(lp,i+1,GLP_FX,(*it)->value,(*it)->value);
        }else if((*it)->type==">="){
            glp_set_row_bnds(lp,i+1,GLP_LO,(*it)->value,0.0);
        }else if((*it)->type=="<="){
            glp_set_row_bnds(lp,i+1,GLP_UP,0.0,(*it)->value);
        }
    }

    //添加约束的系数
    for(size_t i=0;i<m;++i){
        auto it=constraints_collection.begin();
        std::advance(it,i);
        int count_of_binary=(*it)->binary_collection.size();
        int *ind=new int[count_of_binary+1];
        double *val=new double[count_of_binary+1];
        ind[0]=0;
        val[0]=0;//索引0不使用
        for(int j=0;j<count_of_binary;++j){
            auto it2=(*it)->binary_collection.begin();
            std::advance(it2,j);
            ind[j+1]=var_index[(*it2)->name];
            val[j+1]=(*it2)->coefficient;
        }
        glp_set_mat_row(lp,i+1,count_of_binary,ind,val);
        delete[]ind;
        delete[]val;
    }

    //求解0-1整数规划
    glp_iocp parm;
    glp_init_iocp(&parm);    // 初始化参数结构体
    parm.msg_lev = GLP_MSG_ALL;
    glp_simplex(lp,NULL);
    glp_intopt(lp,&parm);

    int num_rows = glp_get_num_rows(lp); // 获取约束数量
    //获取最优解
    double obj_val=glp_mip_obj_val(lp);
    std::cout<<"最优值为: "<<obj_val<<std::endl;
    for(size_t i=0;i<n;++i){
        double val=glp_mip_col_val(lp,i+1);
        if(val==1){
            std::cout<<index_var[i+1]<<"=1"<<std::endl;
        }
    }
}