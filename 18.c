#include "common.h"

enum SQ { OPEN = '.',
          TREE = '|',
          WOOD = '#'};

#define L 50
char buf1[L*(L+1)];
char buf2[L*(L+1)];

#define R 1000000000

int main(void){
    int fd = open("18.txt", O_RDONLY);
    if(read(fd, buf1, sizeof(buf1)) != sizeof(buf1))
        return 1;
    char * st = buf1;
    char * nx = buf2;
    for (int r=0; r<R; r++){
        memcpy(nx, st, sizeof(buf1));
        for(int x=0; x<L; x++) for(int y=0; y<L; y++){
#define COUNT(X, Y, C) if(X+x>=0 && X+x<L && Y+y>=0 && Y+y<L && st[(Y+y)*(L+1)+x+X] == C) s++;
#define COUNTALL(C) ({\
                        int s = 0;\
                        COUNT(-1, -1, C) COUNT(-1, 0, C) COUNT(-1, 1, C)\
                        COUNT(0, -1, C)                  COUNT(0, 1, C) \
                        COUNT(1, -1, C) COUNT(1, 0, C) COUNT(1, 1, C)\
                    s;})
            if(st[y*(L+1)+x] == OPEN){
                if(COUNTALL(TREE) >= 3)
                    nx[y*(L+1)+x] = TREE;
            }else if(st[y*(L+1)+x] == TREE){
                if(COUNTALL(WOOD) >= 3)
                    nx[y*(L+1)+x] = WOOD;
            }else if(st[y*(L+1)+x] == WOOD){
                if(COUNTALL(WOOD) < 1 || COUNTALL(TREE) < 1)
                    nx[y*(L+1)+x] = OPEN;
            }
        }
        SWAP(st, nx);
    }
    int wood = 0, tree = 0;
    for(int x=0; x<L; x++) for(int y=0; y<L; y++){
        if(st[y*(L+1)+x] == WOOD) wood ++;
        if(st[y*(L+1)+x] == TREE) tree ++;
    }
    printf("%d\n", wood * tree);
}   
