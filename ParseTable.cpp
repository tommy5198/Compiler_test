#include"Parser.h"
#include"ParseTable.h"
#include<iostream>
#include<map>
#include<set>
#include<string>
#include<vector>
using namespace std;

extern map<string, Nonterm> Grammar;
map<string, map<string, Pnode> > Ptable;
static map<string, Nonterm>::iterator itr;
static int cnt = 1e9;

bool setPtable(int i, set<string> &st){

    set<string>::iterator sitr = st.begin();
    while(sitr != st.end()){
        Pnode &tmp = Ptable[itr->first][*sitr];
        if(tmp.id > cnt){
            // error
            puts("error in parseTable");
            return false;
        }
        tmp.id = cnt;
        tmp.prod = &itr->prod[i];
        cout << left << setw(20) << itr->first << left << setw(15) << *istr;
        for(int j=0; j<itr->prod[i].size(); j++)
            cout << tmp.prod[i][j] << " ";
        cout << endl;
        ++sitr;
    }
    return true;
}

void parseTable(){
    
    itr = Grammar.begin();
    set<string>::iterator sitr;
    while(itr != Grammar.end()){
        for(int i=0; i<itr->prod.size(); i++){
            int j;
            for(j=0; j<itr->prod[i].size(); j++){
                if(setPtable(getFirst(i, itr->prod[i][j])) == false)
                    return ;
                if(getNullable(itr->prod[i][j]) == false)
                    break;
            }
            if(j == prod[i].size())
                if(setPtable(getFollow(i, itr->first)) == false)
                    return ;
            
            cnt--;
        }
        ++itr;
    }

}


