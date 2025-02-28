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

Token Lexer::parseOperator(){
    std::string op;
    while(ispunct(currentChar)){
        op+=currentChar;
        advance();
    }
    return Token(OPERATOR,op);
}

Token Lexer::parseSeparator(){
    std::string sep;
    sep += currentChar;
    advance();
    return Token(SEPARATOR,sep);
}

Token Lexer::parseBracket(){
    std::string bracket;
    bracket += currentChar;
    advance();
    return Token(BRACKET,bracket);
}

void Lexer::skipWhitespace(){
    while(isspace(currentChar)){
        advance();
    }
}


/**
 * 
 * @brief 获取下一个token
 * 
 * @return token
 *
 */
Token Lexer::NextToken(){
    skipWhitespace();

    if(currentChar=='\0'){
        return Token(END_OF_INPUT,"");
    }

    if(isalpha(currentChar)||currentChar == '_'||currentChar == '$'){
        return parseIdentifier();
    }else if(isdigit(currentChar)){
        return parseNumber();
    }else if(ispunct(currentChar)){
        return parseOperator();
    }else if(currentChar == ';'||currentChar == ','){
        return parseSeparator();
    }else if(currentChar == '['||currentChar == ']'||currentChar == '('||currentChar == ')'){
        return parseBracket();
    }

    std::cerr<<"Unknown character: "<<currentChar<<std::endl;
    exit(1);
}