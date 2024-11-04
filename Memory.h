#ifndef TASK4_MEMORY_H
#define TASK4_MEMORY_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Memory{
private:
    string memory[256];
public:
    Memory(){
        for(int i=0; i<256; i++){
            memory[i]="00";
        }
    }

    void setcell(int address, string value){
        memory[address] = value;
    }

    string getcell(int address){
        return memory[address];
    }

};

#endif
