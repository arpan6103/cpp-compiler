#include "lexer.h"
#include "parser.h"
#include "ir.h"
#include "assembly.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream file("zz.txt");
    if (!file) {
        cerr << "Error: Could not open zz.txt" << endl;
        return 1;
    }

    string source((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    
    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();
    
    Parser parser(tokens);
    vector<shared_ptr<ASTNode>> functions = parser.parse();

    IRGenerator irGen;
    for (const auto& func : functions) {
        func->generateIR(irGen);
    }

    AssemblyGenerator asmGen;
    asmGen.generateAssembly(irGen.instructions);
    asmGen.saveToFile("assembly.s");
    asmGen.printAssembly();

    return 0;
}