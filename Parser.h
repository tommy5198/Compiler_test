#ifndef PARSER_H
#define PARSER_H
#include<vector>
#include<set>
#include<string>
#include<map>
using namespace std;

struct Nonterm{
    vector< vector< string > > prod;
};

bool getNullable(const string&);

set<string>& getFirst(const string&);

set<string>& getFollow(const string&);

#endif

