#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include<vector>
#include<memory>
using namespace std;

class Parser{
    private:
    vector<Token>tokens;
    size_t index=0;

    Token peek();
    Token get();

    void expect(TokenType expected,const string& errormsg);

    shared_ptr<ASTNode>parseBinaryExpression(shared_ptr<ASTNode>left);
    shared_ptr<ASTNode>parseExpression();
    shared_ptr<ASTNode>parseReturn();
    shared_ptr<ASTNode>parseVariableDeclaration();
    shared_ptr<ASTNode>parseFunction();

    public:
    Parser(vector<Token>t);
    vector<shared_ptr<ASTNode>>parse();
};

#endif