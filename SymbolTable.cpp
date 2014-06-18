#include"SymbolTable.h"
#include"Quadruple.h"
#include"Parser.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<map>
#include<set>
#include<string>
#include<cstring>
using namespace std;


Snode Cur;
map<string, map<int, Snode> > Stable;
static ofstream fout("symbol.txt", ofstream::out);
static int stat;
static int CurSp;
static int TopSp;
static int TopMem;
static set<string>::iterator it;
static char type[5];
static int pre[100];
static int t[5];
static int tcnt;
static char op[5];
static int opm;
static char name[5][5];

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
            fout << "var  " << val << endl;
        else
            fout << "func " << val << endl;
    }
    sitem.id = id;
}

int getSym(char *name, int sp){
    while(sp!=-1 && !Stable[name][sp].id)
        sp = pre[sp];
    if(sp==-1){
        cout << "error in getSym, cant find symbol:" << name << endl;
        return -1;
    }
    return Stable[name][sp].value;
}

void Symbol(string Sym, char *next){
        if(!Sym.compare("$"))
 //a           output();
    ;
        tcnt = 0;
        
            if(!Sym.compare("Type")){
            strcpy(type, next);
            stat |= 1;
        }else if(stat&1 && !Sym.compare("id")){
                setSym(1, next, type, CurSp, TopMem);
        }else if(stat&1){
            if(!Sym.compare("num")){
                int tmp;
                sscanf(next, "%d", &tmp);
                TopMem += tmp;
                stat ^= 1;
            }else if(!Sym.compare("epsilon")){
                TopMem++;
                stat ^= 1;
            }
        }
        else if(!Sym.compare("="))
            stat |= 2;
        else if(!Sym.compare("Expr"))
            stat |= 4;
        else if(stat & 4){  // get num or id loca
            if(!Sym.compare("id")){
                t[tcnt] = getSym(next, CurSp);
                strcpy(name[tcnt], next);
                if(t[tcnt++] < 0); // error
            }else if(!Sym.compare("num")){
                int tmp;
                sscanf(next, "%d", &tmp);
                strcpy(name[tcnt], next);
                t[tcnt++] = -tmp;

            }
        }
        else if(!Sym.compare("BinOp") || !Sym.compare("UnaryOp")){
            // set op
            strcpy(op, next);
            opm = !Sym.compare("BinOp") ? 0 : 1;
        }
        else if(stat&4 && getFollow("Expr").find(Sym) != getFollow("Expr").end()){
            // set code
            // store val in t0
            // reset
     //       tcnt--;
               setV(name[tcnt], t[tcnt], 1);
            if(stat&2==0 &&tcnt==1 || stat&2 && tcnt==2)// one 
               setV(name[tcnt], t[tcnt], 1);
            OP(op, opm);
            if(stat&2){
                //--tcnt;
                setV(name[tcnt], t[tcnt], 0);
                strcpy(op, "=");
                OP(op, 1);
                stat ^= 2;
            }
            stat ^= 4;
            if(stat&64 || (stat&128 && !Sym.compare("}"))){
                if(stat&256)
                    setJdis(1);
                setJdis(0);
            }
        }else if(!Sym.compare("FuncHead") || !Sym.compare("{")){
            if(stat&8){
                stat ^= 8;
                return ;
            }
            if(!Sym.compare("FuncHead"))
                stat |= 8;
            pre[++TopSp] = CurSp;
            CurSp = TopSp;
        }else if(!Sym.compare("}"))
            CurSp = pre[CurSp];
        else if(stat&32 && !Sym.compare(")")){
           setJ(0);
           stat ^= 32;
        }
        else if(stat&64 && !Sym.compare("{")){
            stat ^= 64;
            stat |= 128;
        }
        else if(!Sym.compare("if")){
            //branch stat, set cnt
            stat |= 32+64;
        }
        else if(!Sym.compare("else"))
            //branch stat, get cnt for if
            // set cnt & stat
            stat |= 32+64;
        else if(!Sym.compare("while"))
            //branch stat, set cnt
            stat |= 32+64+256;
        else if(stat&16 && !Sym.compare("}")) // cmp with sp }
            // get cnt for branch
            ;
        else if(!Sym.compare("return"))
            // return 
            //setout();
        ;
        else if(stat&256 && !Sym.compare("break"))
            //break by cnt;
            setJdis(1);

}
