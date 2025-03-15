#include "assembly.h"

AssemblyGenerator::AssemblyGenerator(): stackOffset(0){}

void AssemblyGenerator::generateAssembly(const vector<IRInstruction>& irInstructions){
    assemblyCode.push_back(".global _start");
    assemblyCode.push_back(".balign 4");
    assemblyCode.push_back("_start:");

    for(const auto& it:irInstructions){
        if(it.op=="="){
            mapVariable(it.result);
            if(isdigit(it.arg1[0])){
                emit("MOV "+varMap[it.result]+", #"+it.arg1);
            }
            else{
                mapVariable(it.arg1);
                emit("MOV "+varMap[it.result]+", "+varMap[it.arg1]);
            }
        }
        else if(it.op=="+"){
            mapVariable(it.result);
            mapVariable(it.arg1);
            if(isdigit(it.arg2[0])){
                emit("ADD "+varMap[it.result]+", "+varMap[it.arg1]+", #"+it.arg2);
            }
            else{
                emit("ADD "+varMap[it.result]+", "+varMap[it.arg1]+", "+varMap[it.arg2]);

            }
        }
        else if(it.op=="RETURN"){
            mapVariable(it.arg1);
            emit("MOV x0, "+varMap[it.arg1]);
            emit("MOV x16, #1");
            emit("SVC #0");
        }
    }
}

void AssemblyGenerator::mapVariable(const string& var){
    if(varMap.find(var)==varMap.end()){
        varMap[var]="x"+to_string(stackOffset++);
    }
}

void AssemblyGenerator::emit(const string& instruction){
    assemblyCode.push_back("    "+instruction);
}

void AssemblyGenerator::saveToFile(const string& filename){
    ofstream file(filename);
    for(const auto& line:assemblyCode){
        file<<line<<endl;
    }
    file.close();
}

void AssemblyGenerator::printAssembly(){
    for(const auto& it:assemblyCode){
        cout<<it<<endl;
    }
}