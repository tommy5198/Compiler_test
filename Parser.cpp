#include<iostream>
#include<cctype>
#include<cstring>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<string>
#include<stack>
#include<vector>
#include<set>
#include<map>
#include"ParseTable.h"
#include"Parser.h"
#include"Lexer.h"
using namespace std;

char grammar[] = "grammar_modified.txt"; 

int NTcnt, Tcnt;
map<string, Nonterm> Grammar;
map<string, int> Nullable;
map<string, set<string> > First;
map<string, set<string> > Follow;
set<string> ErrorSet;
static stack<string> stk;
static map<string, set<string> > Fre;

int ParserGenerator(char *grammar){
    

}

static void input(){
    
    ifstream fin(grammar, ifstream::in);
    string term, buf, head;
    vector<string> drv;
    int lcnt = 1;
    while(getline(fin, buf)){
        if(buf[0] != ' '){
            head = buf;
        }else{
            stringstream sin(buf);
            drv.clear();
            while(sin >> term){
                drv.push_back(term);
                if(term.compare("epsilon") == 0)
                    Nullable[head] = 1;
            }
            if(head.compare("epsilon") == 0)
                cout << lcnt <<endl;
            lcnt++;
            Grammar[head].prod.push_back(drv);
        }
    }
}

bool getNullable(const string &head){
    if(!isupper(head[0])){
        if(head.compare("epsilon"))
            return false;
        return true;
    }
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
    if(!isupper(head[0])){
        if(head.compare("epsilon"))
            First[head].insert(head);
        return First[head];
    }
    Nonterm &tmp = Grammar[head];
    set<string> &first = First[head];
    set<string>::iterator itr;

    for(int i=0; i<tmp.prod.size(); i++){
        for(int j=0; j<tmp.prod[i].size(); j++){
            if(!isupper(tmp.prod[i][j][0])){
                if(tmp.prod[i][j].compare("epsilon") != 0)
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

set<string>& getFollow(const string &head){
    if(isupper(head[0]))
        return Follow[head];
    return ErrorSet;
}

static void setFollow(){
    map<string, Nonterm>::iterator itr;
    set<string>::iterator sitr;
    set<string> pre;
    bool end = false;
    
    Follow["Program"].insert("$");
    for(itr = Grammar.begin(); itr!=Grammar.end(); ++itr){
        const string &head = itr->first;
        Nonterm &tmp = Grammar[head];
        set<string> &follow = Follow[head]; 
        pre.clear();

        for(int i=0; i<tmp.prod.size(); i++){
            bool nul = true, nulhd = true;
            for(int j=tmp.prod[i].size()-1; ~j; j--){
                string &nw = tmp.prod[i][j];
                if(isupper(nw[0])){
                    if(nulhd){
                        // record follow
                        Fre[head].insert(nw);
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
    }
    while(!end){
        end = true;
        for(itr = Grammar.begin(); itr != Grammar.end(); ++itr){
            set<string> &head = Follow[itr->first];
            set<string> &st = Fre[itr->first];
            for(sitr = st.begin(); sitr != st.end(); ++sitr){
                int sz = Follow[*sitr].size();
                Follow[*sitr].insert(head.begin(), head.end());
                if(end && sz < Follow[*sitr].size())
                    end = false;
            }
        }
    }
}

void SETALL(){

    ofstream fout("set.txt", ofstream::out);
    map<string, Nonterm>::iterator itr;
    
    fout << "Nullable" << endl;
    for(itr = Grammar.begin(); itr!=Grammar.end(); ++itr){
        if(getNullable(itr->first))
            fout << left << setw(20) << itr->first << ":true" << endl;
        else
            fout << left << setw(20) << itr->first << ":false" << endl;
    }

    fout << endl << "First" << endl;
    for(itr = Grammar.begin(); itr!=Grammar.end(); ++itr){    
        set<string> &tmp = getFirst(itr->first);
        set<string>::iterator sitr;
        fout << left << setw(20) << itr->first << ":";
        for(sitr = tmp.begin(); sitr!=tmp.end(); ++sitr)
            fout << *sitr << ' ';
        fout << endl;
    }
   
    setFollow();
    fout << endl << "Follow" << endl;
    for(itr = Grammar.begin(); itr!=Grammar.end(); ++itr){
        set<string> &tmp = getFollow(itr->first);
        set<string>::iterator sitr;
        fout << left << setw(20) << itr->first << ":";
        for(sitr = tmp.begin(); sitr!=tmp.end(); ++sitr)
            fout << *sitr << ' ';
        fout << endl;
    }
}

int main(){
    input();
    SETALL();
    parseTable();
    Lexer();
    return 0;
}
