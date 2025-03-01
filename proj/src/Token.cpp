#include "Token.h"
#include <iostream>

void Token::print(){
    std::cout<<"Token("<<type<<", "<<value<<")"<<std::endl;
}