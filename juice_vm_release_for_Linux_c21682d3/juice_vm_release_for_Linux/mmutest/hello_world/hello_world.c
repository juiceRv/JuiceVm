#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void uart_putchar(unsigned char c)
{
    *(char *)(0x40000000) = c;
}
void uart_puts(unsigned char *s)
{
    while(*s){
        *(char *)(0x40000000) = *s++;
    }
    
}
void main(void)
{
    *(char *)(0x40000000) = 'H';
    *(char *)(0x40000000) = 'E';
    *(char *)(0x40000000) = 'L';
    *(char *)(0x40000000) = 'L';
    *(char *)(0x40000000) = 'O';
    *(char *)(0x40000000) = ' ';
    *(char *)(0x40000000) = 'W';
    *(char *)(0x40000000) = 'O';
    *(char *)(0x40000000) = 'R';
    *(char *)(0x40000000) = 'L';
    *(char *)(0x40000000) = 'D';
    *(char *)(0x40000000) = '\n';
    uart_putchar('c');uart_putchar('\n');
    uart_puts("print string test\n");
}