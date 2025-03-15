#include "parser.h"
#include<iostream>


    Parser::Parser(vector<Token>t) : tokens(std::move(t)){}

    Token Parser::peek(){
        return index<tokens.size() ? tokens[index] : Token{TokenType::END_OF_FILE,""};
    }

    Token Parser::get(){
        return index<tokens.size() ? tokens[index++] : Token{TokenType::END_OF_FILE,""};
    }

    void Parser::expect(TokenType expected,const string& errormsg){
        if(peek().type!=expected){
            cerr<<"Syntax Error: "<<errormsg<<"(found: "<<peek().value<<")"<<endl;
            exit(1);
        }
        get();
    }

    shared_ptr<ASTNode>Parser::parseBinaryExpression(shared_ptr<ASTNode>left){
        while(peek().type==TokenType::OPERATOR){
            char op=get().value[0];
            shared_ptr<ASTNode>right=parseExpression();
            left=make_shared<BinaryOpNode>(op,left,right);
        }
        return left;
    }

    shared_ptr<ASTNode>Parser::parseExpression(){
        Token token=get();
        if(token.type==TokenType::NUMBER){
            return make_shared<NumberNode>(stoi(token.value));
        }
        if(token.type==TokenType::IDENTIFIER){
            return make_shared<IdentifierNode>(token.value);
        }
        cerr<<"Unexpected token in expression: "<<token.value<<endl;
        exit(1);
    }

    shared_ptr<ASTNode>Parser::parseReturn(){
        expect(TokenType::KEYWORD,"Expected 'return' keyword");
        shared_ptr<ASTNode>expr=parseExpression();
        expr=parseBinaryExpression(expr);
        expect(TokenType::PUNCTUATION,"Expected ';' after a statement");
        return make_shared<ReturnNode>(expr);
    }

    shared_ptr<ASTNode>Parser::parseVariableDeclaration(){
        expect(TokenType::KEYWORD,"Expected variable type");
        Token varname=get();
        if(varname.type!=TokenType::IDENTIFIER){
            cerr<<"Syntax Error: Expected variable name"<<endl;
            exit(1);
        }
        expect(TokenType::OPERATOR,"Expected '=' in variable declaration");
        shared_ptr<ASTNode>value=parseExpression();
        value=parseBinaryExpression(value);
        expect(TokenType::PUNCTUATION,"Expected ';' at the end of statement");
        return make_shared<VariableDeclarationNode>(varname.value,value);
    }

    shared_ptr<ASTNode>Parser::parseFunction(){
        expect(TokenType::KEYWORD,"Expected function type");
        Token tokenname=get();
        if(tokenname.type!=TokenType::IDENTIFIER){
            cerr<<"Syntax Error: Expected function name";
            exit(1);
        }
        expect(TokenType::PUNCTUATION,"Expected '(' after function name");
        expect(TokenType::PUNCTUATION,"Expected ')' after function parameters");
        expect(TokenType::PUNCTUATION,"Expected '{' to start function body");

        auto funcnode=make_shared<FunctionDefNode>(tokenname.value);    
        while(peek().type!=TokenType::PUNCTUATION || peek().value!="}"){
            if(peek().type==TokenType::KEYWORD && peek().value=="return"){
                funcnode->body.push_back(parseReturn());
            }
            else if(peek().type==TokenType::KEYWORD){
                funcnode->body.push_back(parseVariableDeclaration());
            }
            else{
                get();
            }
        }
        expect(TokenType::PUNCTUATION,"Expected '}' to end a function");
        return funcnode;
    }

    vector<shared_ptr<ASTNode>>Parser::parse(){
        vector<shared_ptr<ASTNode>>functions;
        while(peek().type!=TokenType::END_OF_FILE){
            functions.push_back(parseFunction());
        }
        return functions;
    }