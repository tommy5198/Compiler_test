#include"Quadruple.h"
#include<string>
#include<vector>
#include<cstdio>
#include<iostream>
#include<fstream>
using namespace std;

struct qua{
    string opcode, arg[2], result;
    int reg[2];
    int mem, ja;

    string Qprint(){
        return this->opcode + '\t' + this->arg[0] + '\t' + this->arg[1] + '\t' + this->result;
    }

    string Tprint(){
        char tmp[5], jmp[5];
        sprintf(tmp, "%d", this->mem);
        sprintf(jmp, "%d", this->ja);
        if(!this->opcode.compare("LD"))
            if(tmp[0] == '-')
                return (string)"LDC " + this->result + "," + (tmp+1) + ",0";
            else
                return this->opcode + " " + this->result + "," + tmp + "(0)";
        else if(!this->opcode.compare("="))
            return (string)"ST " + this->arg[1][1] + "," + tmp + "(0)";
        else if(!this->opcode.compare("m"))
            return (string)"SUB 0,3," + this->arg[0][1];
        else if(!this->opcode.compare("JNE"))
            return (string)"JNE 0," + jmp + "(7)";
        else if(!this->opcode.compare("J"))
            return (string)"LDA 7," + jmp + "(7)";
        else if(!this->opcode.compare("-"))
            return (string)"SUB 0," + this->arg[0][1] + "," + this->arg[1][1];
        else if(!this->opcode.compare("+"))
            return (string)"ADD 0," + this->arg[0][1] + "," + this->arg[1][1];
        else if(!this->opcode.compare("*"))
            return (string)"MUL 0," + this->arg[0][1] + "," + this->arg[1][1];
        else if(!this->opcode.compare("/"))
            return (string)"DIV 0," + this->arg[0][1] + "," + this->arg[1][1];
        else if(!this->opcode.compare("=="))
            return (string)"LDC 0,1,0\n" + "SUB 5," + this->arg[0][1] + "," + this->arg[1][1] + "\n" + "JEQ 5,1(7)\nLDC 0,0,0";
        else if(!this->opcode.compare("!="))
            return (string)"LDC 0,1,0\n" + "SUB 5," + this->arg[0][1] + "," + this->arg[1][1] + "\n" + "JNE 5,1(7)\nLDC 0,0,0";
        else if(!this->opcode.compare("<"))
            return (string)"LDC 0,1,0\n" + "SUB 5," + this->arg[0][1] + "," + this->arg[1][1] + "\n" + "JLT 5,1(7)\nLDC 0,0,0";
        else if(!this->opcode.compare(">"))
            return (string)"LDC 0,1,0\n" + "SUB 5," + this->arg[0][1] + "," + this->arg[1][1] + "\n" + "JGT 5,1(7)\nLDC 0,0,0";
        else if(!this->opcode.compare("<="))
            return (string)"LDC 0,1,0\n" + "SUB 5," + this->arg[0][1] + "," + this->arg[1][1] + "\n" + "JLE 5,1(7)\nLDC 0,0,0";
        else if(!this->opcode.compare(">="))
            return (string)"LDC 0,1,0\n" + "SUB 5," + this->arg[0][1] + "," + this->arg[1][1] + "\n" + "JGE 5,1(7)\nLDC 0,0,0";
        else if(!this->opcode.compare("&&"))
            return (string)"LDC 0,0,0\n" + "JEQ " + this->arg[0][1] + ",2(7)\nJEQ " + this->arg[1][1] + ",1(7)\nLDC 0,1,0";
        else if(!this->opcode.compare("||"))
            return (string)"LDC 0,1,0\n" + "JNE " + this->arg[0][1] + ",2(7)\nJNE " + this->arg[1][1] + ",1(7)\nLDC 0,0,0";

    }
};

vector<qua> QuaCode;
static int arg[2];
static int cnt;
static qua Curq;
static int *Ja;
static char reg[5][3];
static string Asi;
static int Asim, rcnt;
void setV(char *name, int vMem, int mode){ // set arg
    return ;
    if(mode){
        Curq = (qua){"LD", name, "NA", reg[rcnt]};
        Curq.mem = vMem;
        rcnt ^= 1;
        QuaCode.push_back(Curq);
    }else{
        Asi.assign(name);
        Asim = vMem;
    }
        if(Curq.opcode.size() != 2 || !Curq.opcode.compare("LD"))
            *Ja += 1;
        else
            *Ja += 4;
}

void OP(char *op, int opmode){
    // set result in t0
    return ;
    qua tmp;
    if(opmode == 1){
        if(op[0] == '-')
            op[0] = 'm';
        Curq = (qua){op, reg[0], "", "t0"};
    }else if(!opmode){
        if(op[0] != '=')
            Curq = (qua){op, reg[0], reg[1], "t0"};
        else{
            Curq = (qua){op, "t0", "NA", Asi};
            Curq.mem = Asim;
        }
    }
    QuaCode.push_back(Curq);
    cout << QuaCode.size() << endl;
    rcnt = 0;
    if(Curq.opcode.size() != 2 || !Curq.opcode.compare("LD"))
        *Ja += 1;
    else
        *Ja += 4;
}

void setJ(int vMem){    
    // set jump code
    // j dis set by pointer
    return ;
    Curq = (qua){"JNE", "t0", "NA", "t7"};
    QuaCode.push_back(Curq);
    Ja = &QuaCode.back().ja;
}

void setJdis(int dis){
    // set j dis
    Ja = NULL;
}

void output(){
    return ;
    // print quadruple & tm code
    ofstream qout("quadruples.txt", ofstream::out);
    ofstream tmout("code.tm", ofstream::out);
    cout << QuaCode.size() << endl;
    for(int i=0; i<QuaCode.size(); i++){
        qua &Q = QuaCode[i];
        qout << Q.Qprint() << endl;
        qout << Q.Tprint() << endl;
    }

}
