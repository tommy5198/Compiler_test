
int ParserGenerator(char *grammar){
    

    input();
    getNull();
    getFirst();
    getFollow();

}

int NTexist(char *str){
    int i;
    for(i = 0; i<NTcnt; i++)
        if(!memcmp(NonTerm[i].name, str))
            return i;
    return -1;
}

int Texist(char *str){
    int i;
    for(i = 0; i<Tcnt; i++)
        if(!memcmp(Term[i], str))
            return i;
    return -1;
}

void input(){
    
    FILE *fin = fopen(grammar, "r");
    
    int i, idx, Lid, pcnt, pccnt;
    char head;
    char Left[MaxTermlen];
    char prod[MaxTermlen];
    while( (head = fgetc(fin)) != EOF){
        if(head != '\t'){
            
            Left[0] = head;
            fgets(Left+1, MaxTermlen, fin);
            Lid = NTexist(Left);
            if(Lid < 0){
                memcpy(NonTerm[NTcnt].name, Left);
                Lid = NTcnt++;
            }
            pcnt = 0;
        }else{
            while(1){
                fscanf(fin, "%s", prod);
                if(prod[0] < 'a' && NTexist(prod) < 0){
                    memcpy(NonTerm[NTcnt].name, prod); 
                    NonTerm[Lid].set[pcnt][pccnt] = NonTerm[NTcnt++].name;
                }else if(prod[0] >= 'a' && Texist(prod) < 0){
                    memcpy(Term[Tcnt], prod);
                    NonTerm[Lid].set[pcnt][pccnt] = Term[Tcnt++];
                }
                pccnt++;
                if(fgetc(fin) != ' ')
                    break;
            }
        }
        pcnt++;
    }
}
