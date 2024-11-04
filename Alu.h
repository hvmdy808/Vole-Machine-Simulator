#ifndef TASK4_ALU_H
#define TASK4_ALU_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <bitset>
using namespace std;
class ALU{
public:

//    void load1(int reg_i, int mem_i, Register& rege, Memory& memo){
//        rege.setcell(reg_i,memo.getcell(mem_i));
//    }
//    void load2(int reg_i, string val, Register& rege){
//        rege.setcell(reg_i, val);
//    }

    void Rotate(int R , int X , Register& reg){
    //int save =X;
    int dec = hexToDec(reg.getcell(R));
        bitset<8> bin = dec;
        string s = bin.to_string();

        while(X--){
            rotate(s.begin(), s.end() - 1, s.end());
        }
//        for(int i=0; i<save; i++){
//            s[i]='0';
//        }
        dec = stoi(s, nullptr,2);

        reg.setcell(R, decToHex(dec));

    }

    void OR(int S, int T, int R, Register& reg){

        int value = hexToDec(reg.getcell(S))| hexToDec(reg.getcell(T));

        reg.setcell(R, decToHex(value));

    }

    void AND(int S, int T, int R, Register& reg){
        int value = hexToDec(reg.getcell(S)) & hexToDec(reg.getcell(T));
        reg.setcell(R, decToHex(value));

    }

    void XOR(int S, int T, int R, Register& reg){

        int value = hexToDec(reg.getcell(S)) ^ hexToDec(reg.getcell(T));

        reg.setcell(R, decToHex(value));

    }

    int hexToDec(string hexValue){
        int decValue=0;
        int base=1;
        for(int i=hexValue.size()-1; i>=0; i--){
            if(hexValue[i]>='0'&&hexValue[i]<='9'){
                decValue+=(int(hexValue[i]-'0'))*base;
            }else if(hexValue[i]>='A'&&hexValue[i]<='F'){
                decValue+=(int(hexValue[i]-55))*base;
            }
            base=base*16;
        }
        return decValue;
    }

    string decToHex(int decV){
        string hexV="", reversed_ans="";
        char c;
        while(decV!=0){
            int rem=decV%16;
            if(rem<10){
                c=rem+'0';
            }else{
                c=rem+55;
            }
            reversed_ans+=c;
            decV/=16;
        }
        int len=reversed_ans.length();
        for(int i=0; i<len; i++){
            hexV+=reversed_ans[len-1-i];
        }
        string hex2;
        int l= hexV.length();
        while (l<2){
            hex2+='0';
            l++;
        }
        return hex2+hexV;
    }

    string add(string hx1, string hx2){
        long long dec_add= hexToDec(hx1)+ hexToDec(hx2);
        while(dec_add>255){
            dec_add-=256;
        }
        return decToHex(dec_add);
    }

    string decToBin_8bits(int decV){
        string binV="", reversed_ans="";
        char c;
        while(decV!=0){
            int rem=decV%2;
            if(rem==1){
                c=1+'0';
            }else if(rem==0){
                c=0+'0';
            }
            reversed_ans+=c;
            decV/=2;
        }
        int len=reversed_ans.length();
        int rem_zeros=8-len;
        for(int i=0; i<rem_zeros; i++){
            reversed_ans+='0';
        }
        for(int i=0; i<8; i++){
            binV+=reversed_ans[8-1-i];
        }
        return binV;
    }

    int binToDec(string binValue){
        int decValue=0;
        int base=1;
        for(int i=binValue.size()-1; i>=0; i--){
            if(binValue[i]=='1'){
                decValue+=(int(binValue[i]-'0'))*base;
            }
            base=base*2;
        }
        return decValue;
    }

    long double binToFloat(string bin){
        int exp= binToDec(bin.substr(1,3))-4;
        int sign;
        if(bin[0]=='1'){        //1 111 1011 = -5.5
            sign=-1;        // 111
        }else{              //.1011
            sign=1;
        }                                          //0123456
        string mantissa=bin.substr(4,4);    //10.1101
        string unsigned_float;
        if(exp>0){
            for(int i=0; i<4; i++){
                if(exp==i){
                    unsigned_float+='.';
                    unsigned_float+=mantissa[i];
                }else{
                    unsigned_float+=mantissa[i];
                }
            }
        }else if(exp<0){
            unsigned_float="0.";
            for(int i=0; i< abs(exp); i++){
                unsigned_float+='0';
            }
            unsigned_float+=mantissa;
        }else{
            unsigned_float="0."+mantissa;
        }
        //cout<<unsigned_float<<endl;
        int iop;
        for(int i=0; i<unsigned_float.length(); i++){
            if(unsigned_float[i]=='.'){
                iop=i;
                break;
            }
        }
        int int_part= binToDec(unsigned_float.substr(0,iop));
        //cout<<int_part<<endl;
        long double flo=int_part;
        int e=-1;
        for(int i=iop+1; i<unsigned_float.length(); i++){
            flo+=(int(unsigned_float[i]-'0')* pow(2,e));
            e--;
        }
        return sign* flo;
    }

    string decToBin(int decV){
        string binV="", reversed_ans="";
        char c;
        while(decV!=0){
            int rem=decV%2;
            if(rem==1){
                c=1+'0';
            }else if(rem==0){
                c=0+'0';
            }
            reversed_ans+=c;
            decV/=2;
        }
        int len=reversed_ans.length();
        for(int i=0; i<len; i++){
            binV+=reversed_ans[len-1-i];
        }
        return binV;
    }

    string floatAdd(string bin1, string bin2){
        long double num1 = binToFloat(bin1);
        long double num2 = binToFloat(bin2);
        long double n=num1+num2;
        char sign;
        if(n>=0){
            sign='0';
        }else{
            sign='1';
        }
        n= abs(n);
        string float_bin_val;
        float_bin_val+= decToBin(int(n));
        //cout<<"unsigned float"<<n<<' '<<"int part of it: "<<int(n)<<' '<<"dec of int part: "<<decToBin(int(n))<<endl;
        float_bin_val+='.';
        //cout<<"float bin val: "<<float_bin_val<<endl;
        double float_part= n - int(n);
        //cout<<"float dec part: "<<float_part<<endl;
        while(float_part!=0){
            float_part*=2;
            if(float_part>=1){
                float_bin_val+='1';
                float_part--;
            }else{
                float_bin_val+='0';
            }
        }
        if(float_bin_val[0]=='.'){
            float_bin_val='0'+float_bin_val;
        }
        //cout<<"float bin: "<<float_bin_val<<endl;
        int iop, ioms1;
        for(int i=0; i<float_bin_val.length(); i++){
            if(float_bin_val[i]=='.'){
                iop=i;
                break;
            }
        }
        for(int i=0 ;i<float_bin_val.length(); i++){
            if(float_bin_val[i]=='1'){
                ioms1=i;
                break;
            }
        }
        //cout<<"index of point: "<<iop<<' '<<"index of most si 1: "<<ioms1<<endl;
        string mantissa="";             //0123456       //01234
        int exp_of_2;                   //0.00101       //101.1
        if(iop>ioms1){
            exp_of_2=iop-ioms1;
        }else{
            exp_of_2=-(ioms1-1-iop);
        }
        int exp_w_bias=4+exp_of_2;
        //cout<<"power of 2: "<<exp_of_2<<' '<<"pow+bias: "<<exp_w_bias<<endl;
        for(int i=ioms1; i<float_bin_val.length(); i++){
            if(float_bin_val[i]=='1'||float_bin_val[i]=='0'){
                //cout<<i<<endl;
                mantissa+=float_bin_val[i];
            }
        }
        while(mantissa.length()<4){
            mantissa+='0';
        }
        //cout<<"mantissa is: "<<mantissa<<endl;
        string expo= decToBin(exp_w_bias);
        string expo2;
        for(int i=0; i<3-expo.length(); i++){
            expo2+='0';
        }
        expo2+=expo;
        string bin_val=sign+ expo2 +mantissa;
        return bin_val;
    }
};
#endif

