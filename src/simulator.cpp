
/*
Author: Carlos Gabriel Vilas Novas Soares
*/
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "./header/simulator.h"
#include "./header/instructionsTable.h"

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::string;
using std::vector;
using std::map;


string _outputFileName = "myOutputFile.txt";
vector<int> outputValues;
int accumulator = 0, programCounter = 0;
int programError = 0, programEnd = 0;;

void printDataVector(){
    cout <<"PRINTING DATA VECTOR==============================\n";
    for(auto i : dataVector ) cout <<"PC: " << i.programCounter <<endl << "VALUE: " << i.value <<endl;

}

void printRuntimeInfo(){
    cout << "Program Counter <- " << programCounter << endl;
    cout << "Accumulator <- " << accumulator << endl <<endl;
}
vector<string> parseProgram(string readLine){
    string parsed;
    parsed.clear();
    vector<string> parsing;
    for(auto i : readLine){
        if(i == ' ' && !parsed.empty()){
            parsing.push_back(parsed);
            parsed.clear();
        }
        else{
            parsed+=i;
        }
    }
    return parsing;
} 

// Returns variable value based on progam counter position
int getMemValue(string memPc){
    int intMemPc = stoi(memPc);
    for(auto &i : dataVector){
        if(i.programCounter == intMemPc){
            return i.value;
        }
    }
    return 0;
}
// Returns vector element address
Symbol * getMemPosition(string memPc){
    int intMemPc = stoi(memPc);
    for(auto &i : dataVector){
        if(i.programCounter == intMemPc){
            return &i;
        }
    }
}

void mathInstruction (Instruction instruction){
    int value = getMemValue(instruction.parameters.at(0));
    switch(instruction.opcode){
        case 1: accumulator+=value;
            break;
        case 2: accumulator-=value;
            break;
        case 3: accumulator*=value;
            break;
        case 4: accumulator/=value;
            break;
    }   
}       

int jumpInstruction (Instruction instruction, vector<Instruction> codeVector, int &shouldJump){
    // While jumpPc is not  used, it remains in the code for context 
    // jumpPc refers to the programCounter we want to jump to
    // While "index" refers to the index of jumpPc 
    int jumpPc = 0;
    int index = 0;

    for(auto const &i : codeVector){
        if(stoi(instruction.parameters.at(0)) == i.programCounter){
            jumpPc = stoi(i.parameters.at(0));
            break;
        }
        index++;
    }

    if(instruction.opcode == 5){
        return index;
    }
    else if(instruction.opcode == 6){
        if(accumulator<0) {
                shouldJump = 1;
                return index;   
        }

    }
    else if(instruction.opcode == 7){
        if(accumulator>0) {
            shouldJump = 1;
            return index;   
        }
        
    }
    else if(instruction.opcode == 8){
        if(accumulator==0) {
            shouldJump = 1;
            return index;   
        }
        
    }
    return index;
       
}

void copyInstruction (Instruction instruction){
    switch(instruction.opcode){
        case 9:
            Symbol * auxSymbol1 = getMemPosition(instruction.parameters.at(0));
            Symbol * auxSymbol2 = getMemPosition(instruction.parameters.at(1));

            auxSymbol2->value = auxSymbol1->value;
            break;
    }
}

void loadStoreInstruction(Instruction instruction){
    switch(instruction.opcode){
        case 10: 
            accumulator = getMemValue(instruction.parameters.at(0));
            
            break;
        case 11:
            Symbol * auxSymbol = getMemPosition(instruction.parameters.at(0));
            // cout << "value b4: " << auxSymbol->value <<endl;
            // cout << "value accumulator: " <<accumulator <<endl;
            auxSymbol->value = accumulator;

            break;
    }
}

void userInteractionInstruction(Instruction instruction){
    switch(instruction.opcode){

        case 12:{
                Symbol * auxSymbol = getMemPosition(instruction.parameters.at(0));
                cin >> auxSymbol->value;
                break;
            }
        case 13: 
            outputValues.push_back(getMemValue(instruction.parameters.at(0)));
            cout << "OUTPUT: " << getMemValue(instruction.parameters.at(0)) <<endl;
            break; 
    }    
}

void stopInstruction(Instruction instruction){
    programEnd = 1;

}

void runCode(vector<Instruction> codeVector){
    for(int i = 0; i<codeVector.size();i++){
        if(programEnd) return;
       
        programCounter = codeVector.at(i).programCounter;
        if(codeVector.at(i).opcode >= 1 && codeVector.at(i).opcode <= 4){
            mathInstruction(codeVector.at(i));

        }
        else if(codeVector.at(i).opcode>=5 && codeVector.at(i).opcode<=8){
            int shouldJump = 0;
            int auxValue = jumpInstruction(codeVector.at(i), codeVector, shouldJump);
            if(shouldJump == 1){
                i = auxValue -1;
            }
        }
        else if(codeVector.at(i).opcode==9){
            copyInstruction(codeVector.at(i));
        }
        else if(codeVector.at(i).opcode>=10 && codeVector.at(i).opcode<=11){
            loadStoreInstruction(codeVector.at(i));

        }
        else if(codeVector.at(i).opcode>=12 && codeVector.at(i).opcode<=13){
            userInteractionInstruction(codeVector.at(i));

        }
        else if(codeVector.at(i).opcode == 14){

            stopInstruction(codeVector.at(i));

        }
        else{
            cout << "Fatal Error\nUnrecognized instruction\n";
        }
        printRuntimeInfo();
    }
}

vector<Instruction> linkInstructions(vector<string> codeVector){
    programCounter = 0;
    vector<Instruction> instructionsVector;

    for(auto it = codeVector.begin(); it != codeVector.end(); ++it){

        auto searchedMapElement = InstructionsMap.find(stoi(*it));
        Instruction auxInstruction = searchedMapElement->second;
        vector<string> parameters;
        // Add parameter to Instruction, while also incrementing to next number
        for(int i = 0; i < searchedMapElement->second.numberOfParameters;i++){
            it++;
            parameters.push_back(*it);
        }
        auxInstruction.parameters = parameters;
        auxInstruction.programCounter = programCounter;
        programCounter+=searchedMapElement->second.sizeInWords;
        instructionsVector.push_back(auxInstruction);
        if(*it == "14") break;
    }
    return instructionsVector;
}


vector<Symbol> getData(vector<string> codeVector){
    bool isData = false;
    vector<Symbol> auxSymbolVector;

    // Gets correct programCounter for data variables
    for(auto it = codeVector.begin(); it != codeVector.end(); ++it){
        auto searchMap = InstructionsMap.find(stoi(*it));
        it+=searchMap->second.numberOfParameters;
        programCounter+=searchMap->second.sizeInWords;
        if(*it == "14") break;
    }

    for(auto i : codeVector){
        if(isData){
            Symbol auxSymbol(stoi(i), programCounter);
            auxSymbolVector.push_back(auxSymbol);
            programCounter++;
        }
        else{
            if(i == "14"){
                isData = true;
            }
        }
    }

    return auxSymbolVector;
}
void printFile(){
    std::ofstream outputFile;
    outputFile.open(_outputFileName);

    if(!outputFile){
        cout <<"ERROR CREATING FILE\n";
    }
    else{

        for(auto const &i : outputValues) outputFile << i << " ";
        outputFile.close();

    }
}

void openCode(ifstream &inFile, string outputFileName){
    if(!outputFileName.empty()){
        _outputFileName = outputFileName;
    }
    while(!inFile.eof()){
        string readLine;
        getline(inFile,readLine, '\n');
        try{   
            vector<string> codeVector = parseProgram(readLine);
            dataVector = getData(codeVector); 

            vector<Instruction> instructionsVector = linkInstructions(codeVector);

            runCode(instructionsVector);
            printFile();

        }
        catch (int error){
            cout << "Program ended with error.\n";
        }
        
    }

}