#include <stdlib.h>
#include <stdio.h>
#define NEW(...) ({\
    typeof(__VA_ARGS__) * _pt = malloc(sizeof(__VA_ARGS__));\
    *_pt = __VA_ARGS__;\
    _pt;\
})

#define MX 1600
#define MY 2000

typedef struct flow {
    int x;
    int y;
    struct flow * next;
} flow;

enum {SAND, CLAY, DOWN, SIDE, LEFT, RIGHT, UP} grid[MX][MY];

#define CASE break; case
void pgrid(int a, int b, int c, int d){
    for(int y=a; y<b; y++){
        for(int x=c; x<d; x++) switch(grid[x][y]){
            CASE SAND:  printf(".");
            CASE CLAY:  printf("#");
            CASE DOWN:  printf("|");
            CASE SIDE:  printf("~");
            CASE UP:    printf("^");
            CASE LEFT:  printf(">");
            CASE RIGHT: printf("<");
        }
        printf("\n");
    }
}

int main(int argc, char ** argv){
    FILE * f = fopen(argc>1?argv[1]:"17.txt", "r");
    int maxy = 0, miny=MY;
    char rc, cc; 
    int ri, ca, cb;
    while(fscanf(f, "%c=%d, %c=%d..%d\n", &rc, &ri, &cc, &ca, &cb) == 5)
        if(rc == 'x'){
            for(int y=ca; y<=cb; y++){
                grid[ri][y] = CLAY;
                if(y>maxy) maxy = y;
                if(y<miny) miny = y;
            }
        }else{
            if(ri>maxy) maxy = ri;
            if(ri<miny) miny = ri;
            for(int x=ca; x<cb; x++)
                grid[x][ri] = CLAY;
        }
    flow * head, * tail;
    grid[500][miny] = DOWN;
    head = tail = NEW((flow){.x=500, .y=miny});
    int part1 = 0, part2 = 0;
#define GET(X, Y) grid[head->x+X][head->y+Y]
#define SET(X, Y, val) do{ \
        if(head->y+Y<=maxy){ \
            if(GET(X, Y)==SAND) part1++; \
            if(val==UP) part2++; \
            GET(X, Y) = val; \
            tail = tail->next = NEW((flow){.x=head->x+X, .y=head->y+Y}); \
        } \
    }while(0)
    while(head){
        if(GET(0, 0) == DOWN){
            if(GET(0, 1) == SAND) SET(0, 1, DOWN);
            if(GET(0, 1) == CLAY || GET(0, 1) == UP)
                SET(0, 0, SIDE);
        }else if(GET(0, 0) == SIDE){
            if(GET(0, 1) == SAND){
                SET(0, 0, DOWN);
            }else{
                if(GET(-1, 0) == SAND) SET(-1, 0, SIDE);
                if(GET(+1, 0) == SAND) SET(1, 0, SIDE);
                if(GET(-1, 0) == CLAY) SET(0, 0, LEFT);
                if(GET(+1, 0) == CLAY) SET(0, 0, RIGHT);
            }
        }else if(GET(0, 0) == LEFT){
            if(GET(1, 0) == SIDE || GET(1, 0) == SAND)
                SET(1, 0, LEFT);
            if(GET(1, 0) == RIGHT || GET(1, 0) == CLAY)
                SET(0, 0, UP);
        }else if(GET(0, 0) == RIGHT){
            if(GET(-1, 0) == SIDE || GET(-1, 0) == SAND)
                SET(-1, 0, RIGHT);
            if(GET(-1, 0) == LEFT || GET(-1, 0) == CLAY)
                SET(0, 0, UP);
        }else if(GET(0, 0) == UP){
            if(GET(0, -1) == DOWN) SET(0, -1, SIDE);
            if(GET(-1, 0) == LEFT) SET(-1, 0, UP);
            if(GET(1, 0) == RIGHT) SET(1, 0, UP);
        }
        flow * next = head->next;
        free(head);
        head = next;
    }
    //pgrid(miny, maxy, 400, 600);
    printf("%d\n%d\n", part1, part2);
}
