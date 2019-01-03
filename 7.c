#include "stdio.h"

struct {char fr; char to;} pairs[] = {
    #include "7.h"
};

#define LEN(a) (sizeof(a) / sizeof(*a))
#define N 26
#define T 60
#define W 5

struct node {
    int to;
    int fr;
    struct node * l[N];
} nodes[N];

int fin[99999];

void p(int t){
    for(int i=t; i<t+60; i++){
        if(fin[i]) printf(".%08x.", fin[i]);
        else printf(":");
    }
    printf("\n");
}

int main(void){
    for(int i=0; i<LEN(pairs); i++){
        struct node * fr = &nodes[pairs[i].fr - 'A'],
                    * to = &nodes[pairs[i].to - 'A'];
        fr->l[pairs[i].fr++] = to;
        to->to ++;
    }
    int t = 0;
    int workers = W;
    for(int c = 0; c<N; c++){
        printf("%d:", t);
        p(t);
        for(int i=0; i<N && workers; i++){
            if(nodes[i].to == 0){
                fin[t + T + i + 1] |= 1<<i;
                workers --;
                nodes[i].to--;
            }
        }
        while(!fin[t%LEN(fin)]) t++;
        for(int i=0; i<N; i++){
            if((fin[t]>>i) & 1){
                for(int j=0; j<nodes[i].fr; j++)
                    nodes[i].l[j]->to--;
                workers ++;
                fin[t] &= ~(1<<i);
                break;
            }
        }
    }
    printf("%d\n", t);
}
