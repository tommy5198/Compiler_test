#include"SymbolTable.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<map>
#include<string>
#include<cstring>
using namespace std;


Snode Cur;
extern int pre[100];
map<string, map<int, Snode> > Stable;
static ofstream fout("symbol.txt", ofstream::out);

void setSym(int id, char *name, char *tp, int sp, int val){
    Snode &sitem = Stable[name][sp];
    strcpy(sitem.type, tp);
    if(id&1)
        sitem.value = val;
    else{
        int i=0;
        while(i<5 && sitem.parType[i])
            i++;
        if(i<5) sitem.parType[i] = val;
    }
    if(!sitem.id){
        fout << left << setw(10) << name;
        fout << left << setw(6) << tp;
        fout << left << setw(3) << sp;
        if(id&1)
            fout << "var  0" << endl;
        else
            fout << "func 0" << endl;
    }
    sitem.id = id;
}

Snode getSym(char *name, int sp){
    while(~sp && !Stable[name][sp].id)
        sp = pre[sp];
    if(~sp){
        cout << "error in getSym, cant find symbol:" << name << endl;
        return Cur;
    }
    return Stable[name][sp];
}
