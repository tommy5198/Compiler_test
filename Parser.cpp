#include<iostream>
#include<cctype>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include"Parser.h"
using namespace std;

char grammar[] = "grammar_modified.txt"; 

int NTcnt, Tcnt;
map<string, Nonterm> Grammar;
static map<string, int> Nullable;
static map<string, set<string> > First;
static map<string, set<string> > Follow;

int ParserGenerator(char *grammar){
    

}

static void input(){
    
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

bool getNullable(const string &head){
    if(Nullable[head]) 
        return Nullable[head] & 1;
    Nonterm &tmp = Grammar[head];

    for(int i=0; i<tmp.prod.size(); i++){
        bool result = true;
        for(int j=0; j<tmp.prod[i].size(); j++)
            if(!isupper(tmp.prod[i][j][0]) || !getNullable(tmp.prod[i][j])){
                result = false;
                break;
            }
        if(result)
            return Nullable[head] = 1, true;
    }
    return Nullable[head] = 2, false;
}

set<string>& getFirst(const string &head){
    if(!First[head].empty())
        return First[head];
    Nonterm &tmp = Grammar[head];
    set<string> &first = First[head];
    set<string>::iterator itr;

    for(int i=0; i<tmp.prod.size(); i++){
        for(int j=0; j<tmp.prod[i].size(); j++){
            if(!isupper(tmp.prod[i][j][0])){
                first.insert(tmp.prod[i][j]);
                break;
            }else{
                set<string> &st = getFirst(tmp.prod[i][j]);
                first.insert(st.begin(), st.end());
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
    set<string> pre;
    for(int i=0; i<tmp.prod.size(); i++){
        bool nul = true, nulhd = true;
        for(int j=tmp.prod[i].size()-1; ~j; j--){
            string &nw = tmp.prod[i][j];
            if(isupper(nw[0])){
                if(nulhd){
                    // record follow
                    Fe[nw].push_back(head);
                    Fre[head].push_back(nw);
                    nulhd = getNullable(nw);
                }
                Follow[nw].insert(pre.begin(), pre.end());
                if(!getNullable(nw))
                    pre.clear();
                pre.insert(First[nw].begin(), First[nw].end());
            }else{
                nulhd = false;
                pre.clear();
                pre.insert(nw);
            }
        }
    }
    return follow;
}

void dfsFollow(string nw, bool rev){
    vector<string> &vec = rev ? Fre[nw] : Fe[nw];
    vis[nw] = true;
    for(int i=0; i<vec.size(); i++)
        if(!vis[vec[i]])
            dfs(vec[i], rev);
    if(!rev) 
        stk.push(nw);
    else{
        sum.insert(Follow[nw].begin(), Follow[nw].end());
    }
}

int main(){
    input();

    freopen("set.txt", "w", stdout);
    map<string, Nonterm>::iterator itr;
    cout << "Nullable" << endl;
    for(itr = Grammar.begin(); itr!=Grammar.end(); ++itr)
        if(getNullable(itr->first))
            cout << left << setw(20) << itr->first << ":true" << endl;
        else
            cout << left << setw(20) << itr->first << ":false" << endl;
    cout << "First" << endl;
    for(itr = Grammar.begin(); itr!=Grammar.end(); ++itr){
        set<string> &tmp = getFirst(itr->first);
        set<string>::iterator sitr;
        cout << left << setw(20) << itr->first << ":";
        for(sitr = tmp.begin(); sitr!=tmp.end(); ++sitr)
            cout << *sitr << ' ';
        cout << endl;
    }
    
    for(itr = Grammar.begin(); itr!=Grammar.end(); ++itr){
        set<string> &tmp = getFollow(itr->first);
        set<string>::iterator sitr;
        cout << left << setw(20) << itr->first << ":";
        for(sitr = tmp.begin(); sitr!=tmp.end(); ++sitr)
            cout << *sitr << ' ';
        cout << endl;
    }

    return 0;
}
