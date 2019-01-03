#include <stdio.h>
#include <string.h>

#define LEN(a) (sizeof(a)/sizeof(*a))

typedef unsigned char dig;

#define N 919901

dig rec[30000000] = {3, 7};
dig cmp[] = {9, 1, 9, 9, 0, 1};

int main(void){
    int n = 2;
    int e1 = 0,
        e2 = 1;
    dig i = rec[e1] + rec[e2];
    while(n<LEN(cmp) || memcmp(rec+n-LEN(cmp), cmp, sizeof(cmp))){
        if(n == N+10){
            for(int k=N; k<n; k++)
                printf("%d", rec[k]);
            printf("\n");
        }
        if(i>=10){
            rec[n++] = i/10;
            i %= 10;
        }else{
            rec[n++] = i;
            e1 = (e1 + rec[e1] + 1) % n;
            e2 = (e2 + rec[e2] + 1) % n;
            i = rec[e1] + rec[e2];
        }
    }
    printf("%d\n", n - LEN(cmp));
}
