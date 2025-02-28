#include "Lexer.h"

#include <iostream>
/**
 * 
 * 
 * @brier 将当前字符移动一位
 */
void Lexer::advance(){
    position++;
    if(position < input.size()){
        currentChar = input[position];
    }else{
        currentChar = '\0';
    }
}

Token Lexer::parseIdentifier(){
    std::string identifier;
    while(isalnum(currentChar)||currentChar == '_'||currentChar == '$'){
        identifier += currentChar;
        advance();
    }
    if(keywords.count(identifier)){
        return Token(KEYWORD,identifier);
    }else{
        return Token(IDENTIFIER,identifier);
    }
}

Token Lexer::parseNumber(){
    std::string number;
    while(isdigit(currentChar)){
        number +=currentChar;
        advance();
    }
    return Token(NUMBER,number);
}




/**
 * 
 * @brief 获取下一个token
 * 
 * @return token
 *
 */
Token Lexer::NextToken(){

}