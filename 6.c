#include <stdio.h>

struct point{
    int x; int y;
} ps[] = {
#include "6.h"
};

#define N 20000

#define LEN(a) sizeof(a) / sizeof(*a)
#define ABS(x) ((x)>0?(x):-(x))

int sum(int x, int y){
    int s = 0;
    for(int i=0; i<LEN(ps); i++){
        s += ABS(ps[i].x - x) + ABS(ps[i].y - y);
    }
    return s < 10000; 
}

struct point sigs[4] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

int main(void){
    int count = sum(0, 0);
    for(int dist=0; dist < 10000/LEN(ps)+1000; dist++){
        for(int x=0; x<dist; x++){
            for(int g=0; g<4; g++){
                int l = sigs[g].x * (dist - x - (g&1)), 
                    k = sigs[g].y * (x + (g&1));
                count += sum(l, k);
            }
        }
    }
    printf("count: %d\n", count);
}
