#ifndef LEXER_H
#define LEXER_H

#include<iostream>
#include<fstream>
#include<cctype>
#include<vector>
#include<unordered_set>
using namespace std;

enum class TokenType{
    KEYWORD, IDENTIFIER, NUMBER, STRING, OPERATOR, PUNCTUATION, COMMENT, END_OF_FILE
};

struct Token{
    TokenType type;
    string value;
};

class Lexer{
    private:
    string source;
    size_t index;
    unordered_set<string>keywords={"int", "float", "return", "if", "else", "while", "for"};

    public:
    Lexer(const string& src) : source(src),index(0){}
    vector<Token>tokenize();
    char peek();
    char get();
};

#endif