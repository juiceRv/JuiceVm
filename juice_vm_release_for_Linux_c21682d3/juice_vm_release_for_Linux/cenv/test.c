#include <stdio.h>
#include <stdlib.h>
void main(void){
    printf("hello world1\n");
    while(1){
        
        *(char *)(0xA00000) = 0x08;
        *(char *)(0xA00000) = '-';
        *(char *)(0xA00000) = 0x08;
        *(char *)(0xA00000) = '\\';
        *(char *)(0xA00000) = 0x08;
        *(char *)(0xA00000) = '|';
        *(char *)(0xA00000) = 0x08;
        *(char *)(0xA00000) = '/';
        // printf("hello world %d\n",6666666);
    }
}
int puts(const char *s){
    while(*s != 0){
        *(char *)(0xA00000) = *s++;
    }
}
int putchar(const int c){
    *(char *)(0xA00000) = c;
}
int _write (int fd, char *pBuffer, int size)  
{
    for (int i = 0; i < size; i++)
    {   
        *(char *)(0xA00000) = *pBuffer++;
    }  
    return size;
}