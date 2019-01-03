#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static int react(char * buf){
    char * left = buf, 
         * right = buf + 1;
    while(*left){
        while(left >= buf && (*left ^ *right) == 32){
            left --;
            right ++;
        }
        *++left = *right++;
    }
    return left - buf;
}

static void rem(char * buf, char * into, char val){
    do{
        if((*buf|0x60) != val)
            *into++ = *buf;
    }while(*buf++);
}

int main(void){
    char buf[50010] ;//= "dabAcCaCBAcCcaDA";
    char remed[50010];
    int fd = open("5.txt", O_RDONLY);
    read(fd, buf, sizeof(buf));
    *strchr(buf, '\n') = '\0';
    int min = react(buf);
    printf("%d\n", min);
    for(char c='a'; c<='z'; c++){
        rem(buf, remed, c);
        int l = react(remed);
        if(l < min) min = l;
    }
    printf("%d\n", min);
}
