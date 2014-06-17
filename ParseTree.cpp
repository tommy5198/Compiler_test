#include"ParseTable.h"
#include"ParseTree.h"
#include"SymbolTable.h"
#include"Parser.h"
#include<cstdio>
#include<map>
#include<set>
#include<cstring>
#include<string>
#include<stack>
#include<fstream>
#include<iostream>
using namespace std;

extern map<string, map<string, Pnode> > Ptable;
struct stkitem{
    int id;
    string symbol;
};
static stack<stkitem> stk;
static ofstream fout("tree.txt", ofstream::out);

int match(char* Sym, char* next){
    if(stk.empty()){
        stk.push((stkitem){0, "$"});
        stk.push((stkitem){0, "Program"});
    }
    
    while(!stk.empty()){
        stkitem top = stk.top();
        stk.pop();
        Symbol(top.symbol, next);

        if(isupper(top.symbol[0]) && Ptable[top.symbol][Sym].id){
            vector<string> &prod = *(Ptable[top.symbol][Sym].prod);
            for(int i=0; i<top.id*3; i++)
                fout << " ";
            fout << top.id+1 << " " << top.symbol << endl;
            //if(prod[0].compare("epsilon"))
                for(int i=prod.size()-1; ~i; i--)
                    stk.push( (stkitem) {top.id+1, prod[i]} );
        }else if(!isupper(top.symbol[0]) && (!top.symbol.compare("epsilon") || !top.symbol.compare(Sym))){
            for(int i=0; i<top.id*3; i++)
                fout << " ";
            fout << top.id+1 << " " << top.symbol << endl;
            if(!top.symbol.compare("id") || !top.symbol.compare("num")){
                for(int i=0; i<top.id*3+3; i++)
                    fout << " ";
                fout << top.id+2 << " " << next << endl;
            }
            if(top.symbol.compare("epsilon"))
                return 0;
        }else{
            // error
            puts("error in parse tree");
            cout << "--" << Sym << " " << next <<endl << top.symbol<<endl;
            while(!stk.empty()){
                cout<< stk.top().symbol <<endl;
                stk.pop();
            }
            return 1;
        }
    }
    return 0;
}
