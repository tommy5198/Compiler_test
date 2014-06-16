#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#ifdef __cplusplus
extern "C"{
#endif

struct Snode{
    int id;
    char type[5];
    union{
        int value;
        int parType[5];
    };
    Snode(){
        id = 0;
    }
};

void setSym(int, char*, char*, int, int);
Snode getSym(char*, int);

#ifdef __cplusplus
}
#endif

#endif
