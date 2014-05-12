/**
    2014 Compiler course project
    compile specific grammar & code
    
    input:
        main.c
        grammar.txt
    
    output:
        token.txt
        set.txt
        LLtable.txt
        tree.txt
        symbol.txt
        quadruples.txt
        code.tm

    env:
        gcc version 4.6.3
**/

#include<stdio.h>
#include<string.h>
#include<stdlib.h> 


#define MAXlen 1000
#define TOKEN_OUTPUT "token.txt"
#define SET_OUTPUT "set.txt"

int Lexer();               // source code to token list
int ParserGenerator();     // grammar to set(Nullable, First, Follow)
void ParseTable();          // set to parse table
void Parser();              // token list & parse table to parse tree



// asjdoiwfajrfpeajwifeawjf epfjewioafa nfeoiwr392ir90jrag
int main(int argc, char **argv){
    printf("C-- compiler start\n");
    printf("Target code: %s\n", argv[1]);
    if(!Lexer(argv[1]))
        printf("Lexer complete!\n");
    else
        printf("Lexer fail!\n");
    return 0;
}
