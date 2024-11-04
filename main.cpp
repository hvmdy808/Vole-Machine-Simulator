#include <iostream>
#include <fstream>
#include <bitset>
#include "CU.H"
#include "Register.h"
#include "Memory.h"
#include "Machine.h"
#include "CPU.h"
#include "ALU.h"
using namespace std;
int main() {
    Machine machine;
    cout<<"Enter the name of the file of instructions: "<<endl;
    ifstream input_file;
    string file_name;
    cin>>file_name;
    machine.load_file(file_name);
    machine.run_program(); 
    machine.printmem();
    cout<<"================================== \n";
    machine.printreg(); 
    return 0;
}

