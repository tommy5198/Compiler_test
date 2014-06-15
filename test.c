int x ;
int main ( ) {
    int a ;
    int b ;
    char y ;
    a = 1 ;
    if ( a == 1 ) {
        a = 2 ;
    }
    else {
        a = 3 ;
    }
    b = 2 ;
    while ( a > 0 ) {
        b = b + 1 ;
        a = a - 1 ;
    }
    x = a + b ;
    return 0 ;
}
