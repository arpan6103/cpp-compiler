# cpp-compiler
A simple C++ compiler targeting ARM64 assembly


**Structure**

lexer.h and lexer.cpp: 
* Lexer: Responsible for reading and tokenizing the input C++ source code.
* Token: Represents individual units of the source code, such as keywords, identifiers, punctuations etc.
* Functionality: The lexer scans the source code and returns a list of tokens.

parse.h and parser.cpp:
* Parser: Responsible for converting the sequence of tokens produced by lexer into Abstract Syntax Tree (AST).
* Parser Functions: Handles different parts of C++ syntax including var dec, expressions, return statements, and function declaration.
* Error Handling: Ensures the parsed code edheres to C++ grammar, with proper error handling for invalid syntax.

ast.h:
* Abstract Syntax Tree (AST): A heirarchical tree structure the represents the syntax of the C++ code. Each node in the tree represents a program construct, such as an expression, function, or a statement.
* AST nodes: Different types of AST nodes are defined for various constructs in C++, such as:
      * Variable Declaration: Represented as VariableDeclarationNode.
      * Expression: Represented as BinaryOpNode.
      * Return: Represented as ReturnNode.
      * Function Definition: Represented as FunctionDefNode.
* generateIR: Each AST node is responsible for generating its corresponding Intermediate Representation (IR). This is achieved through the generateIR function.

ir.h and ir.cpp: 
* IR (Intermediate Representation): Represnts a lower level version of the program. It is closer to machine instructions but abstract enough for further translation to assembly.
* IR Generator: Responsible for converting AST nodes to IR instructions.
* IRinstruction: Represents an abstract intermediate-level instruction that defines operations (assignment, arithmetic, return) in a generic form.

assembly.h and assembly.cpp
* Assembly Generator: Converts the generated IR into ARM64 assembly instructions. Each IR instruction is mapped to its corresponding ARM64 assembly instruction, such as MOV for moving values into registers and ADD for arithmetic operations.
* Variable Mapping: Maps variables to registers and manages stack offsets as needed.
* Assembly Output: Generates the ARM64 assembly code, which is saved into a assembly.s file. This code can be compiled using an assembler to create machine code.


**Compilation and Execution:**

Prerequisites:
* C++11 or later: The code uses C++11 features like smart pointers.
* ARM64 architecture: The assembly code is designed for ARM64 systems.

To Compile:
* Open terminal
* Go into the project folder, eg: cd desktop/compiler
* Now compile using g++: "g++ -std=c++11 zmain.cpp lexer.cpp parser.cpp ir.cpp assembly.cpp -o compiler"
To run:
* Prepare your source code in the zz.txt file
* Run the Executable file by "./compiler" in the terminal.
The program will save the assembly code in the assembly.s and will print the assembly code in the console.

To further run the assembly code in the assembly.s:
* Assembling into an object file: "as -o mc.o assembly.s"
* Linking: "ld -o mc mc.o -e _start -syslibroot `xcrun --sdk macosx --show-sdk-path` -lSystem"
* Running the Executable: "./mc"
* Display the returned value or result: "echo $?"
