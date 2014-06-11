#ifndef PARSER_H
#define PARSER_H

struct Nonterm{
    vector< vector< string > > prod;
};

bool getNullable(const string&);

set<string>& getFirst(const string&);

set<string>& getFollow(const string&);

#endif

