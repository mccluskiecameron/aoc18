#include <stdio.h>

int power(int S, int x, int y){
    int r = x + 10;
    int p = r * y;
    p += S;
    p *= r;
    p = (p/100)%10;
    p -= 5;
    return p;
}

int grid[300][300];
int main(void){
    for(int y=0; y<300; y++)
        for(int x=0; x<300; x++)
            grid[x][y] = power(1723, x+1, y+1);
    int max = 0, maxx=0, maxy=0, maxn=0;
    int max3 = 0, max3x=0, max3y=0;
    for(int n=1; n<=300; n++){
        for(int x=0; x<=300-n; x++)
            for(int y=0; y<=300-n; y++){
                int P = 0;
                for(int i=0; i<n; i++) for(int j=0; j<n; j++)
                    P += grid[x+i][y+j];
                if(P>max){
                    max = P;
                    maxx = x+1;
                    maxy = y+1;
                    maxn = n;
                }
                if(n==3 && P>max3){
                    max3 = P;
                    max3x = x+1;
                    max3y = y+1;
                }
            }
    }
    printf("%d,%d\n", max3x, max3y);
    printf("%d,%d,%d\n", maxx, maxy, maxn);
}


