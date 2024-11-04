#ifndef TASK4_CU_H
#define TASK4_CU_H
#include <vector>
#include <string>
#include <iostream>
#include "Register.h"
#include "Memory.h"
#include "ALU.h"
using namespace std;
class CU {
public:
    void load1(int reg_i, int mem_i, Register& rege, Memory& memo){
        rege.setcell(reg_i,memo.getcell(mem_i));
    }

    void load2(int reg_i, string val, Register& rege){
        rege.setcell(reg_i, val);
    }

    void store(int reg_i, int mem_i, Register& rege, Memory& memo){
        memo.setcell(mem_i,rege.getcell(reg_i));
    }

};


#endif
