#include "lexer.h"

    char Lexer::peek(){
        if(index<source.size()){
            return source[index];
        }
        else{
            return '\0';
        }
    }

    char Lexer::get(){
        if(index<source.size()){
            return source[index++];
        }
        else{
            return '\0';
        }
    }

    vector<Token>Lexer::tokenize(){
        vector<Token>tokens;
        while(index<source.size()){
            char current=peek();
            if(isspace(current)){
                get();
                continue;
            }

            if(isalpha(current) || current=='_'){
                string word;
                while(isalnum(peek()) || peek()=='_'){
                    word+=get();
                }
                tokens.push_back({keywords.count(word) ? TokenType::KEYWORD : TokenType::IDENTIFIER, word});
                continue;
            }

            if(isdigit(current)){
                string number;
                while(isdigit(peek())){
                    number+=get();
                }
                tokens.push_back({TokenType::NUMBER, number});
                continue;
            }

            if(current=='"'){
                string str;
                get();
                while(peek()!='"' && peek()!='\0'){
                    str+=get();
                }
                if(peek()=='"'){
                    get();
                }
                tokens.push_back({TokenType::STRING, str});
                continue;
            }

            if(current=='/' && peek()=='/'){
                string comment;
                get();
                get();
                while(peek()!='\n' && peek()!='\0'){
                    comment+=get();
                }
                tokens.push_back({TokenType::COMMENT, comment});
                continue;
            }

            if(strchr("+-*/=<>!", current)){
                string op(1, get());
                if(strchr("=<>!", peek())){
                    op+=get();
                }
                tokens.push_back({TokenType::OPERATOR, op});
                continue;
            }

            if(strchr("(){};,", current)){
                tokens.push_back({TokenType::PUNCTUATION, string(1, get())});
                continue;
            }

            cerr<<"Unexpected character: "<<current<<endl;
            get();
        }
        tokens.push_back({TokenType::END_OF_FILE, ""});
        return tokens;
    }