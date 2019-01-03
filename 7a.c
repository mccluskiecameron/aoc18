#include "stdio.h"

struct {char fr; char to;} pairs[] = {
    #include "7.h"
};

#define LEN(a) sizeof(a) / sizeof(*a)

struct node {
    int to;
    int used;
    struct node * l[26];
} nodes[26];

char finished[60*26 + 26*26];

int main(void){
    for(int i=0; i<LEN(pairs); i++){
        struct node * fr = &nodes[pairs[i].fr - 'A'],
                    * to = &nodes[pairs[i].to - 'A'];
        fr->l[pairs[i].to - 'A'] = to;
        to->to ++;
        fr->used = 1;
        to->used = 1;
    }
    int t = 0;
loop:
    for(int i=0; i<26; i++){
        struct node * n = &nodes[i];
        if(n->to == 0 && n->used){ 
            for(int j=0; j<26; j++)
                if(n->l[j])
                    n->l[j]->to--;
            printf("%c", i+'A');
            n->to --;
            goto loop;
        }
    }
    printf("\n");
}
