#include <stdbool.h>
#include <stdio.h>

#define X 400
#define Y 400
bool grid[X][Y];

int max = 0, count = 0;

int parse(FILE * fp, int x, int y, int d){
loop:
    switch(fgetc(fp)){
        case 'N': y++; break;
        case 'E': x++; break;
        case 'S': y--; break;
        case 'W': x--; break;
        case '(': 
            while(parse(fp, x, y, d));
            goto loop;
        case '|': return 1;
        default: return 0;
    }
    d++;
    if(!grid[x][y]){
        grid[x][y]=d;
        if(d>max) max = d;
        if(d>=1000) count ++;
    }
    goto loop;
}

int main(void){
    FILE * fp = fopen("20.txt", "r");
    fgetc(fp);
    parse(fp, X/2, Y/2, 0);
    printf("%d\n%d\n", max, count);
}
