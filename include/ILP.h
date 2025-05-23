#include <fstream>
#include <iostream>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include "Node.h"
#include "helper.h"
class ILP{
    std::map<std::string,size_t> delay_map;//是一个延迟表，存储每一种元件的延迟
    std::set<node*> nodes;
    std::set<std::string> variables_collection;
    node* find_node(const std::string& name);
    void asap();
    void alap(int max_time);
public:
    void set_delay_map(const std::map<std::string,size_t>& delay_map){
        this->delay_map=delay_map;
    }
    void read_blif(const std::string& filename);
    void make_constraints(std::map<std::string,int>& constraints);
};