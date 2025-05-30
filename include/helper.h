#pragma once
#include <string>

bool is_operator(char c);
std::string to_operator_string(std::string str);
void remove_suffix(std::string& str,const std::string& suffix);
bool is_digit_char(char c);