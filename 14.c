#include <stdio.h>
#include <string.h>

#include "chunk.h"
#define LEN(a) (sizeof(a)/sizeof(*a))

typedef unsigned char dig;

#define N 919901

//dig rec[30000000] = {3, 7};
dig cmp[] = {9, 1, 9, 9, 0, 1};

int main(void){
    chunk_t(dig, 10000000) * rec = NULL;
#define AT(i) chunk_at(&rec, i)
    AT(0) = 3;
    AT(1) = 7;
    int n = 2;
    int e1 = 0;
    int e2 = 1;
    dig i = AT(e1) + AT(e2);
    for(;;){
        if(i>=10){
            AT(n++) = i/10;
            i %= 10;
        }else{
            AT(n++) = i;
            e1 = (e1 + AT(e1) + 1) % n;
            e2 = (e2 + AT(e2) + 1) % n;
            i = AT(e1) + AT(e2);
        }
        if(n == N+10){
            for(int k=N; k<n; k++)
                printf("%d", AT(k));
            printf("\n");
        }
        if(n>=LEN(cmp)){
            for(int k=0; k<LEN(cmp); k++)
                if(AT(n+k-LEN(cmp)) != cmp[k] )
                    goto skip;
            printf("%d\n", n - LEN(cmp));
            return 0;
        }
        skip:;
    }
}
