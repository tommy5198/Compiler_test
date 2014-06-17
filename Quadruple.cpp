#include"Quadruple.h"
#include<vector>
using namespace std;

struct qua{
    char opcode[5];
    int arg1, arg2, result;
};

vector<qua> QuaCode;
int arg[2];
int cnt;

void setV(int vMem){ // set arg
    if(vMem < 0)
        arg[cnt^1] = vMem;
    else;
}

void OP(char *op, int opmode){
    // set result in t0
}

void setJ(int vMem){    
    // set jump code
    // j dis set by pointer
}

void setJdis(int dis){
    // set j dis
}

void output(){
    // print quadruple & tm code
}
