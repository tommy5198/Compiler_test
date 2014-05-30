#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include"Parser.h"
using namespace std;

char grammar[] = "grammar_modified.txt"; 
bool Nullable[MaxNonTerm];
struct Nonterm{
    vector< vector< string > > prod;
};

int NTcnt, Tcnt;
map<string, Nonterm> Grammar;

void input();

int ParserGenerator(char *grammar){
    

    input();
    getNullable();
}

void input(){
    
    ifstream fin(grammar, ifstream::in);
    string term, buf, head;
    vector<string> drv;
    
    while(getline(fin, buf)){
        if(buf[0] != ' '){
            head = buf;
        }else{
            stringstream sin(buf);
            drv.clear();
            while(sin >> term){
                drv.push_back(term);
                if(term == "epsilon")
                    Nullable[head] = 1;
            }
            Grammar[head].prod.push_back(drv);
        }
    }
}
 //   for(itr = Grammar.begin(); itr != Grammar.end(); ++itr){
    //map<string, Nonterm> itr;

bool getNullable(string &head){
    if(!Nullable[head]) 
        return Nullable[head] & 1;
    Nonterm &tmp = Grammar[head];

    for(int i=0; i<tmp.prod.size(); i++){
        bool result = true;
        for(int j=0; j<tmp.prod[i].size(); j++)
            if(tmp.prod[i][j][0] >= 'a' || !getNullable(tmp.prod[i][j])){
                result = false;
                break;
            }
        if(result)
            return Nullable[head] = 1, true;
    }
    return Nullable[head] = 2, false;
}

set<string>& getFirst(string &head){
    if(!First[head].empty())
        return First[head];
    Nonterm &tmp = Grammar[head];
    set<string> &first = First[head];
    set<string>::iterator itr;

    for(int i=0; i<tmp.prod.size(); i++){
        for(int j=0; j<tmp.prod[i].size(); j++){
            if(tmp.prod[i][j][0] >= 'a'){
                first.insert(tmp.prod[i][j]);
                break;
            }else if(tmp.prod[i][j][0] < 'a'){
                set<string> &st = getFirst(tmp.prod[i][j]);
                for(itr = st.begin(); itr != st.end(); ++itr)
                    first.insert(itr->first);
                if(!getNullable(tmp.prod[i][j]))
                    break;
            }
        }
    }
    return first;
}

set<string>& getFollow(string &head){
    if(!Follow[head].empty())
        return Follow[head];

    Nonterm &tmp = Grammar[head];
    set<string> &follow = Follow[head];
    set<string>::iterator itr;

    for(int i=0; i<tmp.prod.size(); i++){
        for(int j=0; j<tmp.prod[i].size(); j++){
            if(tmp.prod[i][j][0] < 'a'){
                set<string> &tmp = Follow[tmp.prod[i][j]];
                if(j != tmp.prod[i].size() - 1 && tmp.prod[i][j+1][0] < 'a'){
                    set<string> &ntf = First[tmp.prod[i][j+1]];

                }
            }
        }
    }
    return follow;
}


int main(){
    ParserGenerator(grammar);
}
