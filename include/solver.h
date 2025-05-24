#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<glpk.h>
#include<set>
#include<memory>
#include<map>
class solver{
    private:
        class binary{
            public:
                std::string name;
                int coefficient;
        };

        class constraint{
            public:
                std::set<std::unique_ptr<binary>> binary_collection;
                std::string type;
                int index;
                int value;//表示约束的值
        };
        long long minimum=0;//因为都是正数，所以最小值为0
        std::set<std::unique_ptr<binary>> min_collection;//使用智能指针来管理内存
        std::set<std::unique_ptr<constraint>> constraints_collection;
        std::map<std::string,int> var_index;
        std::map<int,std::string> index_var;

    public:
        void read_file(const std::string& filename);
        void glpk_solver();
};