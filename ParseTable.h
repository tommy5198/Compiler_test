#ifndef PARSETABLE_H
#define PARSETABLE_H
#include<string>
#include<vector>
using namespace std;
struct Pnode{
    int id;
    vector<string> *prod;
};

void parseTable();
#endif
