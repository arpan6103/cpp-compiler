#ifndef AST_H
#define AST_H

#include<iostream>
#include<vector>
#include<memory>
#include<unordered_map>
#include "ir.h"
using namespace std;

enum class NodeType {PROGRAM, FUNCTION_DEF, RETURN, BINARY_OP, IDENTIFIER, NUMBER, VAR_DECL};

struct ASTNode{
    NodeType type;
    virtual ~ASTNode()=default;
    virtual string generateIR(IRGenerator &irGen){return "";}
};

struct NumberNode:ASTNode{
    int value;
    NumberNode(int val) : value(val) {type=NodeType::NUMBER;}
    string generateIR(IRGenerator &irGen) override{
        return to_string(value);
    }
};

struct IdentifierNode:ASTNode{
    string name;
    IdentifierNode(string n) : name(n) {type=NodeType::IDENTIFIER;}
    string generateIR(IRGenerator &irGen) override{
        return name;
    }
};

struct BinaryOpNode:ASTNode{
    char op;
    shared_ptr<ASTNode>left,right;
    BinaryOpNode(char oper, shared_ptr<ASTNode>le, shared_ptr<ASTNode>ri) : op(oper), left(le), right(ri) {type=NodeType::BINARY_OP;}
    string generateIR(IRGenerator &irGen) override{
        if(!left || !right){
            cerr<<"Error! NULL operand in BinaryOpNode: "<<op<<endl;
            exit(1);
        }
        string leftVar=left->generateIR(irGen);
        string rightVar=right->generateIR(irGen);
        string result=irGen.getNewTempVar();
        irGen.emit(string(1,op),leftVar,rightVar,result);
        return result;
    }
};

struct ReturnNode:ASTNode{
    shared_ptr<ASTNode>expr;
    ReturnNode(shared_ptr<ASTNode>ex) : expr(ex) {type=NodeType::RETURN;}
    string generateIR(IRGenerator &irGen) override{
        if(!expr){
            cerr<<"Error! NULL expression in ReturnNode"<<endl;
            exit(1);
        }
        string retval=expr->generateIR(irGen);
        irGen.emit("RETURN", retval,"","");
        return retval;
    }
};

struct VariableDeclarationNode:ASTNode{
    string varName;
    shared_ptr<ASTNode>value;
    VariableDeclarationNode(string name,shared_ptr<ASTNode>val) : varName(name), value(val) {type=NodeType::VAR_DECL;}
    string generateIR(IRGenerator &irGen) override{
        auto valIR=value->generateIR(irGen);
        irGen.addVariable(varName,valIR);
        return varName;
    }
};

struct FunctionDefNode:ASTNode{
    string name;
    vector<shared_ptr<ASTNode>>body;
    FunctionDefNode(string n) : name(n) {type=NodeType::FUNCTION_DEF;}
    string generateIR(IRGenerator &irGen) override{
        irGen.startFunction(name);
        for(const auto& it:body){
            if(it){
                it->generateIR(irGen);
            }
        }
        irGen.endFunction();
        return "";
    }
};

#endif