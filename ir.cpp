#include "ir.h"

IRInstruction::IRInstruction(string o,string a1,string a2,string r) : 
    op(o), arg1(a1), arg2(a2), result(r){}

void IRInstruction::print() const{
    if(op=="RETURN"){
        cout<<op<<" "<<arg1<<endl;
    }
    else if(op=="="){
        cout<<result<<" = "<<arg1<<endl;
    }
    else if(arg2.empty()){
        cout<<result<<" = "<<op<<" "<<arg1<<endl;;
    }
    else{
        cout<<result<<" = "<<arg1<<" "<<op<<" "<<arg2<<endl;
    }
}

IRGenerator::IRGenerator() : tempVarCnt(0){}

string IRGenerator::getNewTempVar(){
    return "t"+to_string(tempVarCnt++);
}

void IRGenerator::emit(string op,string arg1,string arg2,string res){
    instructions.push_back(IRInstruction(op,arg1,arg2,res));
}

void IRGenerator::startFunction(const string& funcname){
    cout<<"Function: "<<funcname<<" {"<<endl;
}

void IRGenerator::endFunction(){
    cout<<"}"<<endl;
}

void IRGenerator::addVariable(const string& varName,const string& value){
    emit("=",value,"",varName);
}

void IRGenerator::printIR() const{
    for(const auto& it:instructions){
        it.print();
    }
}