#ifndef IR_H
#define IR_H

#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct IRInstruction{
    string op;
    string arg1;
    string arg2;
    string result;

    IRInstruction(string o,string a1,string a2,string r);

    void print() const;
};

class IRGenerator{
    public:
    vector<IRInstruction>instructions;
    int tempVarCnt;

    IRGenerator();

    string getNewTempVar();
    void emit(string op,string arg1,string arg2,string res);
    //void emit(string op,string arg1,string res);
    void startFunction(const string& funcname);
    void endFunction();
    void addVariable(const string& varName,const string& value);
    void printIR() const;
};

#endif