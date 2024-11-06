#include <iostream>
#include <fstream>
#include <bitset>
#include "Machine.h"
#include "ALU.h"
#include "CU.h"
#include "Memory.h"
#include "Register.h"
using namespace std;
int main() {
    Machine machine;
    Memory m;
    while(true){
        static int pc=0;
        cout<<"1- Run a program from a file"<<endl;
        cout<<"2- Run an instruction"<<endl;
        cout<<"3- Exit"<<endl;
        string c;
        cin>>c;
        while(c!="1"&& c!="2"&& c!="3"){
            cout<<"Invalid choice, please try again: "<<endl;
            cin>>c;
        }
        if(c=="1"){
            cout<<"Enter the name of the file of instructions: "<<endl;
            ifstream input_file;
            string file_name;
            cin>>file_name;
            machine.load_file(file_name);
            machine.run_program();
            machine.printmem();
            cout<<"================================== \n";
            machine.printreg();
            break;
        }
        else if(c=="2"){
            string inst;
            cout<<"Please enter the instruction: "<<endl;
            cout<<"Note that instructions of jumping ot halting can not be executed as it is, only can be accessed in a complete program"<<endl;
            cin>>inst;
            while(!machine.is_valid(inst) || inst[0]=='C' || inst[0]== 'B' || inst[0]== 'D'){
                cout<<"invalid instruction, try again: "<<endl;
                cin>>inst;
            }
            m.setcell(pc, inst.substr(0,2));
            m.setcell(pc+1, inst.substr(2,2));
            pc+=2;
            machine.execute_command(inst);
            cout<<"Memory state: "<<endl;
            for (int i = 0; i < 256; i++) {
                if((i+1)%16==0){
                    cout<<m.getcell(i)<<' ';
                    cout<<endl;
                }else{
                    cout<<m.getcell(i)<<' ';
                }
            }
            cout<<"================================== \n";
            machine.printreg();
        }else{
            break;
        }
    }
}

