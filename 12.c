#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef int64_t i64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#define LEN(a) (sizeof(a) / sizeof(*a))
#define SWAP(a, b) do{          \
        typeof(a) c = a;        \
        a = b;                  \
        b = c;                  \
    }while(0)

char init[] = "#........#.#.#...###..###..###.#..#....###.###.#.#...####..##..##.#####..##...#.#.....#...###.#.####";
char * change[] = { "#..##", ".", "##..#", "#", "..##.", ".", ".##.#", "#", ".....", ".", "..###", "#", "###.#", "#", 
                    "#....", ".", "#.##.", "#", ".#.##", "#", "#...#", ".", "...##", ".", "###..", "#", ".#..#", ".", 
                    "####.", ".", "....#", ".", "#####", "#", ".###.", ".", "#..#.", ".", "##...", "#", ".#...", "#", 
                    "#.#.#", ".", "..#..", "#", "...#.", "#", "##.#.", ".", ".##..", "#", ".#.#.", ".", "#.#..", ".", 
                    "..#.#", "#", "#.###", ".", "##.##", ".", ".####", "#",};

//char init[] = "#..#.#..##......###...###";
//char * change[] = { "...##", "#", "..#..", "#", ".#...", "#", ".#.#.", "#", ".#.##", "#", ".##..", "#", ".####", "#", "#.#.#", "#", "#.###", "#", "##.#.", "#", "##.##", "#", "###..", "#", "###.#", "#", "####.", "#"};

#define SLICE(num, c, d) ((num & ~((~0)<<(d))) >> (c))

#define L 2
#define R 1000
#define C 50000000000

#define IND(k) ((k)/8)
#define BIT(k) ((k)%8)
#define NUM(k) (IND(k)+(BIT(k)?1:0))

u8 T[32];
u8 GT[1<<24];

int main(void){
    for (int i=0; i<LEN(change)/2; i++){
        u8 val = 0;
        for(int k=0; k<5; k++)
            if(change[i*2][k]=='#') 
                val |= (1<<k);
        T[val] = *change[i*2+1]=='#';
    }
    for(int i=0; i<LEN(GT); i++){
        int v = 0, w = 0, x = 0;
        for(int k=0; k<20; k++) v |= T[SLICE(i, k, k+5)]<<k;
        for(int k=0; k<16; k++) w |= T[SLICE(v, k, k+5)]<<k;
        for(int k=0; k<12; k++) x |= T[SLICE(w, k, k+5)]<<k;
        for(int k=0; k<8; k++) GT[i] |= T[SLICE(x, k, k+5)]<<k;
    }

    u8 * st = malloc(NUM(L+R) * sizeof(u8));
    u8 * nx = malloc(NUM(L+R) * sizeof(u8));

    int i;
    for(i=0; init[i]; i++){
        if(!BIT(i+L)) 
            st[IND(i+L)] = 0;
        if(init[i] == '#')
            st[IND(i+L)] |= (1<<BIT(i+L));
    }

    i64 l = IND(L),
        r = IND((i-1)+L),
        shift = 0;
    
    for(i64 i=0; i<C/4; i++){
        i64 s = l-IND(L);
        shift += s;
        for(i64 k=l-1; k<=r+1; k++)
            nx[k-s] = GT[SLICE(*(u32*)(st+k-1), 0, 24)];
        l = nx[l-1] ? l-1 : nx[l] ? l : l+1;
        r = nx[r+1] ? r+1 : nx[r] ? r : r-1;
        SWAP(st, nx);
    }

    i64 S = 0;
    for(i64 i=l-1; i<=r+1; i++)
        for(int k=0; k<8; k++)
            if(st[i] & (1<<k))
                S += ((i+shift)*8 + k) - L;
    printf("%ld\n", S);
}
