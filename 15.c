#include "common.h"

typedef struct Unit {
    int x;
    int y;
    int h;
    int g;
} Unit;

typedef struct Force {
    Unit units[100];
    int n;
} Force;
#define EACH(f, v) for(int v=0; v<(f)->n; v++)

Force elves;
Force gobs;

#define TERR(x, y) buf[(y)*(w+1)+(x)]
char buf[1057];
int w, h;
Unit circle[] = {{0, -1}, {-1, 0}, {+1, 0}, {0, +1}};
int elf_strength;

Unit * find(int x, int y, Force * f){
    EACH(f, i)
        if(f->units[i].x == x && f->units[i].y == y)
            return &f->units[i];
    return NULL;
}

void attack(Unit * un, Force * f){
    Unit * as = NULL;
    Unit * a;
    for(int c=0; c<LEN(circle); c++)
        if((a = find(un->x+circle[c].x, un->y+circle[c].y, f)))
            as = as && as->h<=a->h ? as : a;
    if(!as) return;
    if(f == &elves)
        as->h -= 3;
    else
        as->h -= elf_strength;
    if(as->h <= 0)
        *as = f->units[--f->n];
}

int unit_cmp(Unit * a, Unit * b, void *k){
    struct {int d[w][h];} * j = k;
    return  j->d[b->x][b->y] - j->d[a->x][a->y] ?: 
            b->y - a->y ?:
            b->x - a->x;
}

void go(Unit * un, Force * friends, Force * foes){
    Unit pars[w][h];
    int distances[w][h]; 
    memset(distances, 0x7f, sizeof(distances));
    distances[un->x][un->y] = 0;
    Unit to_visit[w*h];
    to_visit[0] = *un;
    int nto_visit = 1;
    while(nto_visit){
        Unit cur = to_visit[--nto_visit];
        if(find(cur.x, cur.y, foes)){
            Unit step;
            int away = 0;
            while(cur.x != un->x || cur.y != un->y){
                away ++;
                step = cur;
                cur = pars[cur.x][cur.y];
            }
            if(away>1){
                un->x = step.x;
                un->y = step.y;
            }
            if(away<3)
                attack(un, foes);
            break;
        }
        for(int c=0; c<LEN(circle); c++){
            Unit n = {cur.x+circle[c].x, cur.y+circle[c].y};
            if(TERR(n.x, n.y)=='#' || find(n.x, n.y, friends))
                continue;
            int nd = distances[cur.x][cur.y] + 1;
            if(nd < distances[n.x][n.y]){
                distances[n.x][n.y] = nd;
                pars[n.x][n.y] = cur;
                to_visit[nto_visit++] = n;
            }
        }
        qsort_r(to_visit, nto_visit, sizeof(Unit), (int (*)(const void *, const void*, void*))unit_cmp, distances);
    }
    un->g = 1;
}

void disp(void){
    for(int x=0; x<w; x++) for(int y=0; y<h; y++)
        if(TERR(x, y) == 'E' || TERR(x, y) == 'G')
            TERR(x, y) = '.';
    EACH(&elves, e)
        TERR(elves.units[e].x, elves.units[e].y) = 'E';
    EACH(&gobs, g)
        TERR(gobs.units[g].x, gobs.units[g].y) = 'G';
    puts(buf);
}

void healthes(void){
    EACH(&elves, e)
        printf("E: %d\n", elves.units[e].h);
    EACH(&gobs, g)
        printf("G: %d\n", gobs.units[g].h);
}

Unit * _choose(Unit cur, Force * f){
    Unit * res = NULL;
    EACH(f, i) if(!f->units[i].g && (cur.y - f->units[i].y ?: cur.x - f->units[i].x) >= 0){
        cur.x = f->units[i].x;
        cur.y = f->units[i].y;
        res = &f->units[i];
    }
    return res;
}

int choose(void){
    Unit * elf = _choose((Unit){w, h}, &elves),
         * gob = _choose(elf?*elf:(Unit){w, h}, &gobs);
    if(gob)
        go(gob, &gobs, &elves);
    else if(elf)
        go(elf, &elves, &gobs);
    else
        return 0;
    return 1;
}

int main(int argc, char ** argv){
    if(argc>1) elf_strength = atoi(argv[1]);
    else       elf_strength = 3;
    int fd = open("15-test.txt", O_RDONLY);
    int n = read(fd, buf, LEN(buf));
    w = strchr(buf, '\n') - buf;
    h = n / (w+1);
    for(int x=0; x<w; x++) for(int y=0; y<h; y++){
        if(TERR(x, y) == 'E')
            elves.units[elves.n++] = (Unit){x, y, 200, 0};
        if(TERR(x, y) == 'G')
            gobs.units[gobs.n++]   = (Unit){x, y, 200, 0};
    }
    int start_len = elves.n;
    int rounds = -1;
    while(elves.n && gobs.n){
        rounds++;
        disp();
        healthes();
        while(choose());
        EACH(&elves, i) elves.units[i].g = 0;
        EACH(&gobs, i)  gobs.units[i].g = 0;
    }
    int S = 0;
    EACH(&elves, i) S += elves.units[i].h;
    EACH(&gobs, i)  S += gobs.units[i].h;
    printf("H: %d\n", S * rounds);
    if(start_len == elves.n)
        return 0;
    return 1;
}
