#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

struct line{
    int x; int y;
    int vx; int vy;
} lines[310];

void sz(int * w, int * h){
    struct winsize sz;
    ioctl(1, TIOCGWINSZ, &sz);
    *w = sz.ws_col;
    *h = sz.ws_row;
}

int display(struct line * lines, int n, int m){
#define VAL(c) (lines[i].c + lines[i].v ## c * m)
    int mx = 999999;
    int my = 999999;
    int Mx = -999999;
    int My = -999999;
    int w, h;
    sz(&w, &h);
    for(int i=0; i<n; i++){
        if(VAL(x) < mx) mx = VAL(x);
        if(VAL(y) < my) my = VAL(y);
        if(VAL(x) > Mx) Mx = VAL(x);
        if(VAL(y) > My) My = VAL(y);
    }
    int dx, dy;
    if(Mx-mx < w) dx = w;
    else dx = Mx-mx;
    if(My-my < h) dy = h;
    else dy = My-my;
    printf("\x1b[2J");
    for(int i=0; i<n; i++){
        printf("\x1b[%d;%dH*", 
            (VAL(y)-my)*h/dy,
            (VAL(x)-mx)*w/dx);
    }
    return dx * dy;
#undef VAL
}

#define CASE break; case

char buf[10];
int main(void){
    FILE * f = fopen("10.txt", "r");
    int n = 0;
    while(4 == fscanf(f, "%d\t%d\t%d\t%d\n", &lines[n].x, &lines[n].y, &lines[n].vx, &lines[n].vy))
        n++;
    int k = 0;
    struct termios newt;
    tcgetattr(0, &newt);
    newt.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &newt);
    char c;
    while(read(0, &c, 1)){
        switch(c){
            CASE 'a': k += 1;
            CASE 's': k += 10;
            CASE 'd': k += 100;
            CASE 'f': k += 1000;
            CASE 'A': k -= 1;
            CASE 'S': k -= 10;
            CASE 'D': k -= 100;
            CASE 'F': k -= 1000;
            CASE 'q': return 0;
        }
        int metric = display(lines, n, k);
        printf("\x1b[20H%d  %d", k, metric);
        fflush(stdout);
    }
}
