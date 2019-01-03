#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sparse.h"

#define ABS(c) ((c)>=0?(c):-(c))

int bump(FILE * fp, int * f){
    int a;
    if(fscanf(fp, "%d\n", &a) == EOF) 
        return 1;
    *f += a;
    return 0;
}

void a(char * fn){
    FILE * fp = fopen(fn, "r");
    int f = 0;
    while(!bump(fp, &f))
        ;
    printf("%d\n", f);
    fclose(fp);
}

void bumpb(FILE * fp, int * f){
    while(bump(fp, f))
        rewind(fp);
}

void b(char * fn){
    FILE * fp = fopen(fn, "r");
    sparse s = {.n=0};
    for(int f=0; sparse_push(&s, ABS(f)<<1 | (f<0)); bumpb(fp, &f);)
        ;
    printf("%d\n", f);
    fclose(fp);
}

int main(void){
    a("1.txt");
    b("1.txt");
}
