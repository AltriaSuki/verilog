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
    else return str;
}