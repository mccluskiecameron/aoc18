#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "uthash.h"
#include <stdbool.h>
#include <inttypes.h>

#include "new.h"

#define SWAP(a, b) do{          \
        typeof(a) c = a;        \
        a = b;                  \
        b = c;                  \
    }while(0)

int count(char c, char * line){
    int i = 0;
    for(; *line; line++){
        if(*line == c) i++;
    }
    return i;
}

int has_n(char * line, int n){
    for(char c=0; c<127; c++){
        if(count(c, line) == n)
            return 1;
    }
    return 0;
}

void a(char * fn){
    char buf[128];
    FILE * fp = fopen(fn, "r");
    int c2 = 0;
    int c3 = 0;
    while(fgets(buf, 128, fp)){
        c2 += has_n(buf, 2);
        c3 += has_n(buf, 3);
    }
    printf("%d\n", c2*c3);
    fclose(fp);
}

typedef struct trie {
    bool term;
    struct trie * vals[256];
} trie;

int trie_push_n(trie * t, char * s, int n){
    if(!*s){
        int ret = 1;
        SWAP(t->term, ret);
        return ret;
    }
    if(n==0)
        s++;
    trie ** loc = &t->vals[(uint8_t)*s];
    if(!*loc) *loc = NEW((trie){.term=0});
    return trie_push_n(*loc, s+1, n-1);
}

int trie_push_all(trie * t, char * s){
    for(int i=0; s[i]; i++)
        if(s[i] != s[i+1]) // don't insert the same thing twice !
            if(trie_push_n(t, s, i))
                return i;
    return -1;
}

void print_n(char * s, int n){
    if(!*s)return;
    if(n!=0) 
        printf("%c", *s);
    print_n(s+1, n-1);
}

void _trie_printall(trie * t, char * buf, int i){
    if(t->term){
        buf[i] = '\0';
        printf("%s\n", buf);
    }
    for(uint8_t c=0; c<127; c++){
        if(t->vals[c]){
            buf[i] = c;
            _trie_printall(t->vals[c], buf, i+1);
        }
    }
}

void trie_printall(trie * t){
    char buf[128];
    _trie_printall(t, buf, 0);
}

void trie_free(trie * t){
    for(uint8_t c=0; c<127; c++){
        if(t->vals[c])
            trie_free(t->vals[c]);
    }
    free(t);
}

void b(char * fn){
    char buf[128];
    FILE * fp = fopen(fn, "r");
    trie * t = NEW((trie){.term=0});
    while(fgets(buf, 128, fp)){
        *strchrnul(buf, '\n') = '\0';
        int n = trie_push_all(t, buf);
        if(n>=0){
            printf("match:");
            print_n(buf, n);
            printf("\n");
            break;
        }
    }
    //trie_printall(t);
    trie_free(t);
    fclose(fp);
}

int main(int argc, char ** argv){
    char * fn;
    if(argc<2)
        fn = "2.txt";
    else
        fn = argv[1];
    //a(fn);
    b(fn);
}
