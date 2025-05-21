#include "helper.h"


bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%'
            || c == '=' || c == '!' || c == '<' || c == '>' 
            || c == '&' || c == '|' || c == '^'||c=='@');
}

std::string to_operator_string(std::string str){
    if (str == "+") return "add";
    else if (str == "-") return "sub";
    else if (str == "*") return "mul";
    else if (str == "/") return "div";
    else if (str == "%") return "mod";
    else if (str == "=") return "eq";
    else if (str == "!") return "not";
    else if (str == "<") return "lt";
    else if (str == ">") return "gt";
    else if (str == "&") return "and";
    else if (str == "|") return "or";
    else if (str == "^") return "xor";
    else if (str == "@") return "at";
    else if (str == "==")return "eq";
    else if (str == "!=") return "ne";
    else if (str == "<=") return "le";
    else if (str == ">=") return "ge";
    else return str;
}

void remove_suffix(std::string& str, const std::string& suffix){
    if (str.length() >= suffix.length() && str.compare(str.length() -suffix.length(), suffix.length(),suffix)==0){
        str.erase(str.length() - suffix.length());
    }
}