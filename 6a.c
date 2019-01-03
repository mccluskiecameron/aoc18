#include <stdio.h>
#include <time.h>

struct point{
    int x; int y;
} ps[] = {
//    {1, 1}, {1, 6}, {8, 3},
//    {3, 4}, {5, 5}, {8, 9},
#include "6.h"
};

#define N 800
#define OFF N/3
#define LEN(a) sizeof(a) / sizeof(*a)

int d[N][N];
int n[N][N];

int areas[LEN(ps)];
int stop[LEN(ps)];

struct point sigs[4] = {{-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

int main(int argc, char ** argv){
    for(int i=0; i<LEN(ps); i++){
        int l = ps[i].x + OFF,
            k = ps[i].y + OFF;
        d[l][k] = 1;
        n[l][k] = i+1;
    }
    for(int dist=1; dist<N; dist++){
        for(int i=0; i<LEN(ps); i++){
            if(stop[i])continue;
            stop[i] = 1;
            for(int x=0; x<dist; x++){
                for(int g=0; g<4; g++){
                    int l = ps[i].x + OFF + sigs[g].x * (dist - x - (g&1)), 
                        k = ps[i].y + OFF + sigs[g].y * (x + (g&1));
                    if(l >= N || l<0 || k >= N || k<0)
                        return 0;
                    if(n[l][k] == 0){
                        d[l][k] = dist+1;
                        n[l][k] = i+1;
                        areas[i]++;
                    }else if(n[l][k] > 0 && d[l][k] == dist+1){
                        areas[n[l][k]-1]--;
                        n[l][k] = -1;
                        d[l][k] = -1;
                    }else{
                        continue;
                    }
                    stop[i] = 0;
                }
            }
            if(stop[i] == 1){
                printf("%d: %d\n", i, areas[i]+1);
            }
        }
    }
}
