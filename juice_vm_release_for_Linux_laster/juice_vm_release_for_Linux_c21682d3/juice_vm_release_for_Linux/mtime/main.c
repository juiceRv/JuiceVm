#include <stdio.h>
#include <stdlib.h>
#include <rv_mtvec_map.h>

#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) ({ \
  if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
    asm volatile ("csrw " #reg ", %0" :: "i"(val)); \
  else \
    asm volatile ("csrw " #reg ", %0" :: "r"(val)); })


void main(void){
    // *(uint64_t *)(pdev_mtime_mtimecmp_addr+1) = 300;
    uint64_t i;
    while(1){
        i = 1000;
        while(i--);
        // printf("wait for cb\n");
    }
}
void execption_handle(uint64_t mcause){
    // printf("execption_handle %x\n",mcause);
    if(mcause & 0x7){
        printf("mtime cb\n");
    }
}
int puts(const char *s){
    while(*s != 0){
        *(char *)(0xA00000) = *s++;
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