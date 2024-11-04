#ifndef TASK4_REGISTER_H
#define TASK4_REGISTER_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;
class Register{
private:
    string reg[16];
public:
    Register(){
        for(int i=0; i<16; i++){
            reg[i]="00";
        }
    }

    void setcell(int address, string value){
        reg[address] = value;
    }

    string getcell(int address){
        return reg[address];
    }

};
#endif
