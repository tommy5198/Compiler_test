#include"Lexer.h"
#include<regex.h>

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
