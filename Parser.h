
char Term[MaxNoTerm][MaxTermlen];
int Nullable[NoNonTerm];
struct Nonterm{
        char name[MaxTermlen];
            char *set[MaxNoProd][MaxNoProdConcat];
}NonTerm[MaxNoNonTerm], First[MaxNoNonTerm], Follow[MaxNoNonTerm];

