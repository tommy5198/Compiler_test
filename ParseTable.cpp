#include"Parser.h"
#include"ParseTable.h"
#include<cstdio>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<map>
#include<set>
#include<string>
#include<vector>
using namespace std;

extern map<string, Nonterm> Grammar;
map<string, map<string, Pnode> > Ptable;
static map<string, Nonterm>::iterator itr;
static int cnt = 1e9;
static ofstream fout("table.txt", ofstream::out);

static bool setPtable(int i, set<string> &st){
    
    set<string>::iterator sitr = st.begin();
    while(sitr != st.end()){
        Pnode &tmp = Ptable[itr->first][*sitr];
        tmp.prod = &itr->second.prod[i];
        fout << left << setw(20) << itr->first << left << setw(15) << *sitr;
        for(int j=0; j<tmp.prod->size(); j++)
            fout << tmp.prod->at(j) << " ";
        fout << endl;
        if(tmp.id > cnt){
            // error
            puts("error in parseTable");
            return false;
        }
        tmp.id = cnt;
        ++sitr;
    }
    return true;
}

void parseTable(){
    
    itr = Grammar.begin();
    set<string>::iterator sitr;
    fout << "S" << endl;
    while(itr != Grammar.end()){
 //       cout << itr->first << endl;
        for(int i=0; i<itr->second.prod.size(); i++){
            int j;
            for(j=0; j<itr->second.prod[i].size(); j++){
                if(setPtable(i, getFirst(itr->second.prod[i][j])) == false){
                    puts("Conflict");
                    return ;
                }
                if(getNullable(itr->second.prod[i][j]) == false)
                    break;
            }
            if(j == itr->second.prod[i].size())
                if(setPtable(i, getFollow(itr->first)) == false){
                    puts("Conflict");
                    return ;
                }
            
            cnt--;
        }
        ++itr;
    }
}


