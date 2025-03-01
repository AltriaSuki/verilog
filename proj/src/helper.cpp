#include "helper.h"


bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%'
            || c == '=' || c == '!' || c == '<' || c == '>' 
            || c == '&' || c == '|' || c == '^' || c == '~' 
            || c == ',' || c == '.' || c == ';');
}