#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "ir.h"
#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>
using namespace std;

class AssemblyGenerator{
    public:
    vector<string>assemblyCode;
    unordered_map<string,string>varMap;
    int stackOffset;

    AssemblyGenerator();

    void generateAssembly(const vector<IRInstruction>& irInstructions);
    void mapVariable(const string& var);
    void emit(const string& instruction);
    void saveToFile(const string& filename);
    void printAssembly();
};

#endif