#include "common.h"
int test(int RES){
    int C = 920;
    int D;
    if(RES) C = 10551320;
    RES = 0;
    int E = 1;
    int B = 1;
    while(1){
        if(B >= C){
            E ++;
            if(E > C) return RES;
            B = 0;
        }
        B++;
        if(E*B < C && B < C){
            if(C%E == 0)
                B = C/E;
            else
                B = C;
        }
        if(E*B == C) RES += E;
        if(B < C)
            B = C;
    }


}

int main(){
    printf("%d\n", test(1));
}
