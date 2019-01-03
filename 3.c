#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ints.h"

#define N 1000

u8 data[N][N]; 

void a(char * fn){
    FILE * fp = fopen(fn, "r");
    int n, x, y, w, h;
    while(fscanf(fp, "%d %d %d %d %d\n", &n, &x, &y, &w, &h) == 5){
        for(int i=x; i<x+w; i++) for(int j=y; j<y+h; j++)
            data[i][j] += 1;
    }
    int c = 0;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(data[i][j] > 1)
                c ++;
    printf("%d\n", c);
}

void b(char * fn){
    FILE * fp = fopen(fn, "r");
    int n, x, y, w, h;
next:
    if(fscanf(fp, "%d %d %d %d %d\n", &n, &x, &y, &w, &h) == 5){
        for(int i=x; i<x+w; i++) for(int j=y; j<y+h; j++)
            if(data[i][j] != 1) goto next;
        printf("%d\n", n);
        return;
    }
    printf("none\n");
}

int main(int argc, char ** argv){
    char * fn;
    if(argc<2)
        fn = "3m.txt";
    else
        fn = argv[1];
    a(fn);
    b(fn);
}
