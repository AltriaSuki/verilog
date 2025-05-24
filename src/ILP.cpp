#include "Node.h"
#include "ILP.h"
node* ILP::find_node(const std::string& name){
    for(auto& n:nodes){
            if(n->name==name){
                return n;
            }
        }
    return nullptr;
}

void ILP::read_blif(const std::string& filename){
    std::ifstream file(filename);
        if(!file.is_open()){
            std::cerr<<"Error opening file: "<<filename<<std::endl;
            return;
        }
        std::unordered_set<std::string> inputs;
        std::unordered_set<std::string> outputs;
        std::string line;
        while(std::getline(file,line)){
        read_name://读取了.name来避免重新读取行
            if(line.find(".inputs")!=std::string::npos){
                std::istringstream iss(line);
                std::string token;
                while(iss>>token){
                    if(token!=".inputs"){
                        inputs.insert(token);
                    }
                }
            }else if(line.find(".outputs")!=std::string::npos){
                std::istringstream iss(line);
                std::string token;
                while(iss>>token){
                    if(token!=".outputs"){
                        outputs.insert(token);
                    }
                }
            }else if(line.find(".names")!=std::string::npos){
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> predecessor;
                std::string successor;
                while(iss>>token){
                    if(token!=".names"&&!inputs.count(token)){
                        predecessor.push_back(token);
                        auto it=find_node(token);
                        if(it){
                            continue;
                        }
                        node* new_node=new node();
                        new_node->name=token;
                        new_node->already_scheduled=false;
                        new_node->start_time_in_asap=0;
                        new_node->delay=0;
                        
                        nodes.insert(new_node);//将节点添加到集合中,如果已经存在则不添加
                    }
                }
                predecessor.pop_back();
                successor=token;
                node* succ_node=find_node(successor);
                //完全不用关心input
                for(auto& pred:predecessor){
                    node* pred_node=find_node(pred);
                    if(pred_node){
                        pred_node->successors.insert(succ_node);
                        succ_node->predecessors.insert(pred_node);
                    }
                }

                while(getline(file,line)){
                    if(line.empty()){
                        break;
                    }else if(line.find(".end")!=std::string::npos||line.find(".name")
                            !=std::string::npos){
                        //整理一下关系，然后跳出循环
                        goto read_name;
                }else{
                    if(line.find("0")!=std::string::npos){
                        succ_node->delay=delay_map["NOT"];
                        succ_node->type="NOT";
                        break;
                    }else if(line.find("-")!=std::string::npos){
                        succ_node->delay=delay_map["OR"];
                        succ_node->type="OR";
                        break;
                    }else if(line.find("1")!=std::string::npos){
                        succ_node->delay=delay_map["AND"];
                        succ_node->type="AND";
                        break;
                    }
                }
                
            }
        }
    }

    file.close();
    node* dummy_node=new node();
    dummy_node->name="D";
    dummy_node->type="DUMMY";
    //插入虚拟节点
    dummy_node->already_scheduled=false;
    nodes.insert(dummy_node);
    for(auto& n:nodes){
        if(n->successors.empty()&&n->type!="DUMMY"){
            n->successors.insert(dummy_node);
            dummy_node->predecessors.insert(n);
        }
    }
}

void ILP::asap(){
     std::queue<node*> pq;
    for(auto& n:nodes){
        if(n->predecessors.empty()){
            n->start_time_in_asap=1;
            pq.push(n);
        }
    }
    while(!pq.empty()){
        node* current=pq.front();
        pq.pop();
        if(current->already_scheduled){
            continue;
        }
        current->already_scheduled=true;
        for(auto& pre:current->predecessors){
            current->start_time_in_asap=std::max(current->start_time_in_asap,pre->start_time_in_asap+pre->delay);
        }
        for(auto& succ:current->successors){
            bool all_scheduled=true;
            for(auto& pre:succ->predecessors){
                if(!pre->already_scheduled)
                    all_scheduled=false;
            }
            if(all_scheduled){
                pq.push(succ);
            }
        }
    }
}

void ILP::alap(int max_time){
    for(auto& n:nodes){
        n->already_scheduled=false;
        n->start_time_in_alap=max_time-n->delay;
    }
    std::queue<node*> pq;
    for(auto& n:nodes){
        if(n->successors.empty()){
            pq.push(n);
        }
    }
    while(!pq.empty()){
        node* current=pq.front();
        pq.pop();
        if(current->already_scheduled){
            continue;
        }
        current->already_scheduled=true;
        for(auto& succ:current->successors){
            current->start_time_in_alap=std::min(current->start_time_in_alap,succ->start_time_in_alap-current->delay);
        }
        for(auto& pre:current->predecessors){
            bool all_scheduled=true;
            for(auto& succ:pre->successors){
                if(!succ->already_scheduled)
                    all_scheduled=false;
            }
            if(all_scheduled){
                pq.push(pre);
            }

        }
    }
}
//三个约束
//唯一约束、顺序约束、资源约束
//最小化最后一个结点的开工时间
//constraint表示的是资源有多少
//ML—RCS
void ILP::make_constraints(std::map<std::string,int>& constraint){
    const std::string filename="./output/output.lp";
    std::ofstream file(filename);
    if(!file.is_open()){
        std::cerr<<"Error opening file: "<<filename<<std::endl;
        return;
    }
    int lambda=0;
    asap();
    for(auto& n:nodes){
        if(n->type=="DUMMY"){
            lambda=n->start_time_in_asap;
            break;
        }
    }
    alap(lambda);
    for(auto& n:nodes){
        n->range[n->start_time_in_asap]=n->start_time_in_alap+n->delay;
    }
    file<<"Min"<<std::endl;
    for(int i=1;i<=lambda;++i){
        if(i==1){
            file<<"XD"+std::to_string(i)<<" ";
            variables_collection.insert("XD"+std::to_string(i));
        }else{
            file<<std::to_string(i)<<"XD"+std::to_string(i)<<" ";
            variables_collection.insert("XD"+std::to_string(i));
        }
        if(i!=lambda){
            file<<"+ ";
        }
    }
    file<<std::endl;
    file<<"subject to"<<std::endl;
    //唯一约束
    file<<"unique:"<<std::endl;
    for(auto& n:nodes){
        for(int i=n->start_time_in_asap;i<=n->start_time_in_alap;++i){
            file<<"X"<<n->name<<std::to_string(i)<<" ";
            variables_collection.insert("X"+n->name+std::to_string(i));
            if(i!=n->start_time_in_alap){
                file<<"+ ";
            }
        }
        file<<"= 1"<<std::endl;
    }
    //顺序约束
    file<<"sequence:"<<std::endl;
    for(auto& n:nodes){
        for(auto& pre:n->predecessors){
            for(int i=n->start_time_in_asap;i<=n->start_time_in_alap;++i){
                if(i==1){
                    file<<"X"+n->name+std::to_string(i)<<" ";
                    variables_collection.insert("X"+n->name+std::to_string(i));
                }else{
                    file<<std::to_string(i)+"X"+n->name+std::to_string(i)<<" ";
                    variables_collection.insert("X"+n->name+std::to_string(i));
                }
                if(i!=n->start_time_in_alap){
                    file<<"+ ";
                }
            }
            for(int i=pre->start_time_in_asap;i<=pre->start_time_in_alap;++i){
                file<<"- ";
                file<<std::to_string(i)+"X"+pre->name+std::to_string(i)<<" ";
                variables_collection.insert("X"+pre->name+std::to_string(i));
            }
            file<<">= 1"<<std::endl;
        }
    }
    //资源约束
    file<<"resource:"<<std::endl;
    for(int i=1;i<=lambda+1;++i){
        for(auto&resource:constraint){
            std::string result;
            int delay=delay_map[resource.first];
            bool has_exec=false;
            for(int j=i-(delay-1);j<=i;++j){
                if(j<1){
                    continue;
                }
                //双重累加可以交换位置
                for(auto& n:nodes){
                    if(n->type==resource.first){
                        if(j>=n->start_time_in_asap&&j<=n->start_time_in_alap){
                            result+="X"+n->name+std::to_string(j)+" + ";
                            variables_collection.insert("X"+n->name+std::to_string(j));
                            has_exec=true;
                        }
                    }
                }
            }
            if(!has_exec){
                continue;
            }
            std::string temp="+ ";
            remove_suffix(result,temp);
            result+="<= "+std::to_string(resource.second);
            file<<result<<std::endl;
        }
    }
    file<<"binary"<<std::endl;
    for(auto& n:variables_collection){
        file<<n<<std::endl;
    }
    file<<"end"<<std::endl;
}