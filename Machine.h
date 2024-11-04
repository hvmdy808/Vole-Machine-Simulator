#ifndef TASK4_MACHINE_H
#define TASK4_MACHINE_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "ALU.h"
#include "Register.h"
#include "Memory.h"
#include "CU.h"
using namespace std;

bool fileloaded = true;


class Machine : public Memory, public Register, public ALU, public CU{
    Memory m;
    Register r;
    ALU a;
    CU c;
public:
    void load_file(string fn) {
        ifstream x(fn);
        if (!x.is_open()) {
            cout << "Failed to open the file" << endl;
            cout << "Program terminated" << endl;
            fileloaded = false;
            exit(0); // Exit the function if file can't be opened
        }
        string line;
        int i = 0;
        while (getline(x, line)) {
            if (line.size() < 4) continue; // Skip lines that are too short
            string code = line.substr(0, 4); // Read the first 4 characters
            if (is_valid(code)) {
                m.setcell(i, code.substr(0, 2));   // Set first 2 chars
                m.setcell(i + 1, code.substr(2, 2)); // Set next 2 chars
                i += 2;
            } else {
                cout << "Invalid code: " << code << endl; // Handle invalid codes
                exit(0);
            }
        }
        x.close();
    }

    bool is_valid(string code) {
        const string hex = "0123456789ABCDEF"; // Valid hexadecimal characters
        if (code.size() != 4) {
            return false;
        }
        for (int i = 0; i < 4; i++) {
            if (hex.find(code[i]) == string::npos) {
                return false;
            }
        }
        return true;
    }

    void execute_command(string line) {
        if (line[0] == '1') {
            string s(1, line[1]);
            //r.setcell(a.hexToDec(s), m.getcell(a.hexToDec(line.substr(2, 2))));
            c.load1(a.hexToDec(s) , a.hexToDec(line.substr(2,2)) , r,m);
        }
        if (line[0] == '2') {
            string s(1, line[1]);
            //r.setcell(a.hexToDec(s), line.substr(2, 2));
            c.load2(a.hexToDec(s) , line.substr(2,2) , r);
        }
        if (line[0] == '3' && !(line[2] == '0' && line[3] == '0')) {
            string s(1, line[1]);
            //m.setcell(a.hexToDec(line.substr(2, 2)), r.getcell(a.hexToDec(s)));
            c.store(a.hexToDec(s) , a.hexToDec(line.substr(2,2)) , r,m);
        }
        if (line[0] == '3' && line[2] == '0' && line[3] == '0') {
            string s(1, line[1]);
            c.store(a.hexToDec(s) , a.hexToDec(line.substr(2,2)) , r,m);
            cout << "Number printed to screen by the simulator : " << r.getcell(a.hexToDec(s)) << endl;
        }
        if (line[0] == '4') {
            string s(1, line[2]);
            string s2(1, line[3]);
            r.setcell(a.hexToDec(s2), r.getcell(a.hexToDec(s)));
        }
        if (line[0] == '5') {
            string s(1,line[1]);
            string s1(1,line[2]);
            string s2(1,line[3]);
            r.setcell(a.hexToDec(s),a.add(r.getcell(a.hexToDec(s1)),r.getcell(a.hexToDec(s2))));
        }
        if(line[0]=='6'){
            string re(1, line[1]);
            string s(1, line[2]);
            string t(1, line[3]);
            int dec1=a.hexToDec(r.getcell(a.hexToDec(s)));
            int dec2=a.hexToDec(r.getcell(a.hexToDec(t)));
            string bin8b_1 = a.decToBin_8bits(dec1);
            string bin8b_2 = a.decToBin_8bits(dec2);
            string bin_added = a.floatAdd(bin8b_1, bin8b_2);
            string hex_val = a.decToHex(a.binToDec(bin_added));
            r.setcell(a.hexToDec(re), hex_val);
        }
        if(line[0]=='7'){
            string R(1,line[1]);
            string s(1, line[2]);
            string t(1, line[3]);
            a.OR(a.hexToDec(s), a.hexToDec(t), a.hexToDec(R), r);
        }
        if(line[0]=='8'){
            string R(1,line[1]);
            string s(1, line[2]);
            string t(1, line[3]);
            a.AND(a.hexToDec(s), a.hexToDec(t), a.hexToDec(R), r);
        }
        if(line[0]=='9'){
            string R(1,line[1]);
            string s(1, line[2]);
            string t(1, line[3]);
            a.XOR(a.hexToDec(s), a.hexToDec(t), a.hexToDec(R), r);
        }
        if(line[0]=='A'){
            string s(1, line[1]);
            a.Rotate(a.hexToDec(s), line[3]-'0', r);
        }

    }

    void run_program() {
        int PC = 0;
        while (true) {
            string code = m.getcell(PC) + m.getcell(PC + 1);
            if (!is_valid(code)) {
                cout << "Invalid code found at line " << (PC / 2) + 1 << "!\n";
                break;
            }
            if (code[0] == 'C') {
                break;
            }
            if (code[0] == 'B') {
                string s(1, code[1]);
                if (a.hexToDec(r.getcell(a.hexToDec(s))) == a.hexToDec(r.getcell(0))) {
                    PC = a.hexToDec(code.substr(2, 2));
                } else {
                    PC += 2;
                    continue;
                }
            }
            if(code[0]=='D'){
                string s(1, code[1]);
                if (a.hexToDec(r.getcell(a.hexToDec(s))) > a.hexToDec(r.getcell(0))) {
                    PC = a.hexToDec(code.substr(2, 2));
                } else {
                    PC += 2;
                    continue;
                }
            }
            else {
                execute_command(code);
                PC += 2;
            }
        }
    }

    void printmem() {
        cout<<"Memory state: "<<endl;
        for (int i = 0; i < 256; i++) {
            if((i+1)%16==0){
                cout<<m.getcell(i)<<' ';
                cout<<endl;
            }else{
                cout<<m.getcell(i)<<' ';
            }
        }
    }

    void printreg() {
        cout<<"Register state: "<<endl;
        for (int i = 0; i < 16; i++) {
            if (i == 0) {
                cout << "00" << " - " << r.getcell(i) << endl;
            } else if (i <= 15) {
                cout << a.decToHex(i) << " - " << r.getcell(i) << endl;
            }
        }
    }
};

#endif
