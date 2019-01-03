#include "common.h"

#define IP 1

int regs[6] = {0};
enum instr{ADDR, ADDI, MULR, MULI, SETI, SETR, GTRR, EQRR};

struct op{ enum instr i; int a, b, c;} ops[] = {
    #include "19.h"
};

void run(){
    struct op op = ops[regs[IP]];
    int a = op.a, b = op.b, c = op.c;
    switch(op.i){
        CASE ADDR: regs[c] = regs[a] + regs[b];
        CASE MULR: regs[c] = regs[a] * regs[b];
        CASE ADDI: regs[c] = regs[a] + b;
        CASE MULI: regs[c] = regs[a] * b;
        CASE GTRR: regs[c] = regs[a] > regs[b];
        //CASE GTRI: regs[c] = regs[a] > b;
        //CASE GTIR: regs[c] = a > regs[b];
        CASE EQRR: regs[c] = regs[a] == regs[b];
        //CASE EQRI: regs[c] = regs[a] == b;
        //CASE EQIR: regs[c] = a == regs[b];
        CASE SETI: regs[c] = a;
        CASE SETR: regs[c] = regs[a];
    }
    regs[IP] ++;
}

void dump_reg(){
    for(int i=0; i<LEN(regs); i++){
        printf("%d ", regs[i]);
    }
    printf("\n");
}

int main(void){
    while(regs[IP] < LEN(ops)){
        run();
        dump_reg();
    }
    printf("%d\n", regs[0]);
}
