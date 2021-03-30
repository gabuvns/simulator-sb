#ifndef __INSTRUCTIONSTABLE_H_
#define __INSTRUCTIONSTABLE_H_

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;
using std::map;


struct Instruction{
    string simbolicOpcode;
    int opcode = 0;
    int programCounter = 0;
    int sizeInWords = 0;
    int numberOfParameters = 0; 
    vector<string> parameters;
    
    Instruction(string simbolicOpcode, int opcode, int sizeInWords, int numberOfParameters){
        this->simbolicOpcode = simbolicOpcode;
        this->opcode = opcode;
        this->sizeInWords = sizeInWords;
        this->numberOfParameters = numberOfParameters;  
    }
    Instruction(){}
};

struct Symbol{
    int value = 0;
    int programCounter = 0;
    Symbol(int value, int pc){
        this->value =  value;
        this->programCounter = pc;
    }
};
vector<Symbol> dataVector;

const map<int, Instruction> InstructionsMap{
    // {"ADD", Instruction(simboliocOpcode, opcode, sizeInWords, numberOfParameters)}     
    {1,   Instruction("ADD"  , 1, 2, 1)},     
    {2,   Instruction("SUB"  , 2, 2, 1)},
    {3,   Instruction("MUL"  , 3, 2, 1)},
    {4,   Instruction("DIV"  , 4, 2, 1)},
    {5,   Instruction("JMP"  , 5, 2, 1)},
    {6,   Instruction("JMPN" , 6, 2, 1)},
    {7,   Instruction("JMPP" , 7, 2, 1)},
    {8,   Instruction("JMPZ" , 8, 2, 1)},
    {9,   Instruction("COPY" , 9, 3, 2)},
    {10,  Instruction("LOAD" , 10, 2, 1)},
    {11,  Instruction("STORE", 11, 2, 1)},
    {12,  Instruction("INPUT", 12, 2, 1)},
    {13,  Instruction("OUTPUT", 13, 2, 1)},
    {14,  Instruction("STOP" , 14, 1, 0)},
};

#endif