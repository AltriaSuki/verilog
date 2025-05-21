#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>
#pragma once
class node{
    public:
        std::string name;
        std::string type;
        std::unordered_set<node*> successors;
        std::unordered_set<node*> predecessors;
        std::map<int,int> range;
        int start_time_in_asap;
        int start_time_in_alap;
        int delay;
        bool already_scheduled;
        int depth=0;
        bool inqueue=false;
};