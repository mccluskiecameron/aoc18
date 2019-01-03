#include <inttypes.h>
#include <stdio.h>

#define LEN(a) (sizeof(a)/sizeof(*a))

uint64_t p[403];
struct node{int n; int p;} ns[71920*100 + 1];

static int ins(int a, int b){
    ns[b].n = ns[a].n;
    ns[b].p = a;
    ns[a].n = b;
    ns[ns[b].n].p = b;
    return b;
}

static int rem(int a){
    ns[ns[a].p].n = ns[a].n;
    ns[ns[a].n].p = ns[a].p;
    return ns[a].n;
}

int main(void){
    int c = 0;
    for(int i = 1; i<LEN(ns); i++){
        if(i%23){
            c = ins(ns[c].n, i);
        }else{
            for(int k=0; k<7; k++)
                c = ns[c].p;
            p[i%LEN(p)] += c+i;
            c = rem(c);
        }
    }
    uint64_t max = 0;
    for(int i=0; i<LEN(p); i++)
        if(p[i] > max) max = p[i];
    printf("%lu\n", max);
}
