#include <stdio.h>
#include <stdlib.h>
#include <rv_mtvec_map.h>
void main(void){
    // *(uint64_t *)(pdev_mtime_mtimecmp_addr+1) = 300;
    uint64_t i;
    puts("main\n");
    extern void main_blinky( void );
    main_blinky();
    puts("main_blinky\n");
    while(1){
        i = 1000;
        while(i--);
        puts("wait for cb\n");
    }
}
void execption_handle(uint64_t mcause){
    // printf("execption_handle %x\n",mcause);
    if(mcause & 0x7){
        printf("mtime cb\n");
    }
}
void vSendString( const char * pcString )
{

	while( *pcString != 0x00 )
	{
		*(char *)(pdev_uart0_write_addr) = *pcString;
		pcString++;
	}
}
int puts(const char *s){
    while(*s != 0){
        *(char *)(pdev_uart0_write_addr) = *s++;
    }
}
// int _write (int fd, char *pBuffer, int size)  
// {
//     for (int i = 0; i < size; i++)
//     {   
//         *(char *)(0xA00000) = *pBuffer++;
//     }  
//     return size;
// }
