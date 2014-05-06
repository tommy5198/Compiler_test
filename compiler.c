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
#include<regex.h>

#define MAXlen 1000
#define TOKEN_OUTPUT "token.txt"
#define SET_OUTPUT "set.txt"

int Lexer();               // source code to token list
void ParserGenerator();     // grammar to set(Nullable, First, Follow)
void ParseTable();          // set to parse table
void Parser();              // token list & parse table to parse tree

// Lexer generate source code to token list, if success return 0, else return 1
int Lexer(char *source){
    
    // FILE IO 
    FILE *fin = fopen(source, "r");
    FILE *fout = fopen(TOKEN_OUTPUT, "w");
    
    // regex structure
    regex_t *reg_obj[7];
    const char *reg_des[7] = {
                    "<Keyword>",
                    "<Operator>",
                    "<Special>",
                    "<Identifier>",
                    "<Number>",
                    "<Char>",
                    "<Comment>"
    };
    const char *reg_exp[7] ={ 
                    "^(int|char|return|if|else|while|break)$",          // Keys     
                    "^(=|!|\\+|-|\\*|/|==|!=|<|>|<=|>=|&&|\\|\\|)$",    // Ops
                    "^(\\[|\\]|\\(|\\)|\\{|\\}|;|,)$",                  // Sps
                    "^[a-zA-z_][a-zA-Z0-9_]*$",                         // Id
                    "^[0-9]+$",                                         // Num
                    "^\'[.|\\n|\\t| ]\'$",                              // Char
                    "^//$"                                              // Com
    };

    int i, reg_error, line;
    char str[MAXlen]; 
    char *token, *sptr;

    // compile reg_exp to reg_obj
    for(i=0; i<7; i++){
        reg_obj[i] = (regex_t*) calloc(1, sizeof(regex_t));
        if(reg_error = regcomp(reg_obj[i], reg_exp[i], REG_EXTENDED | REG_NOSUB)){
            // reg error
            fprintf(stdout, "reg_exp[%d] in regcomp error\nerror code: %d\n", i, reg_error);
            fclose(fin);
            fclose(fout);
            return 1;
        }
    }
    
    // genarate source code to token list
    fprintf(stdout, "generate token list from %s to %s\n", source, TOKEN_OUTPUT);
    for(line = 1; fgets(str, MAXlen, fin); line++){ 
        // get one line
        fprintf(fout, "Line %d:\n", line);

        // spilt a line by space, tab or newline
        for(token = strtok(str, " \t\r\n"); token; token = strtok(NULL, " \t\r\n")){

            // match reg_obj
            for(i=0; i<7; i++)
                if(!(reg_error = regexec(reg_obj[i], token, 0, 0, 0)) ){
                    // is matched
                    fprintf(fout, "\t%s\t: %s\n", reg_des[i], token);
                    break;
                }

            if(i == 7){
                // not matched
                fprintf(stdout, "Lexer error!\nline %d: unknown token \"%s\"\n", line, token);
                fclose(fin);
                fclose(fout);
                return 1;
            }
        }
    }
    return 0;
}

char Term[NoTerm][Termlen];
int Nullable[NoNonTerm];
struct Nonterm{
    char *name;
    char *set[NoProd][NoProdConcat];
}nonterm[NoNonTerm], First[NoNonTerm], Follow[NoNonTerm];

// asjdoiwfajrfpeajwifeawjf epfjewioafa nfeoiwr392ir90jrag
int ParserGenerator(char *grammar){
    
    // set FILE IO
    FILE *fin = fopen(grammar, "r");
    FILE *fout = fopen(SET_OUTPUT, "w");

    
}
int main(int argc, char **argv){
    printf("C-- compiler start\n");
    printf("Target code: %s\n", argv[1]);
    if(!Lexer(argv[1]))
        printf("Lexer complete!\n");
    else
        printf("Lexer fail!\n");
    return 0;
}
