#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_bin.h"
// uint64_t mmu_test_pagetable[512] __attribute__((section(".frist_pte_addr"))) ;
#define SATP_SV39 (8L << 60)
#define RV64_MMU_SV39_PAGESIZE  (4*1024)
#define RV64_MMU_SV39_PTESIZE   (8)

#define MAKE_SATP(pagetable) (SATP_SV39 | (((uint64_t)pagetable) >> 12))
int puts(const char *s);
// Supervisor address translation and protection
static inline void w_satp(uint64_t x){
    // char tmp_str[30];
    // sprintf(tmp_str,"w_satp %064x\n",x);
    // puts(tmp_str);
    asm volatile("csrw satp, %0"::"r"(x));
}

static inline uint64_t r_satp(){
    uint64_t x;
    asm volatile("csrr %0, satp":"=r"(x));
    return x;
}
#define PTE_V (1L << 0) // valid
#define PTE_R (1L << 1)
#define PTE_W (1L << 2)
#define PTE_X (1L << 3)
#define PTE_U (1L << 4) // 1 -> user can access

#define get_VPN2_va(xva)   ((xva>>30)&0x1ff) 
#define get_VPN1_va(xva)   ((xva>>21)&0x1ff) 
#define get_VPN0_va(xva)   ((xva>>12)&0x1ff) 
#define get_vo_va(xva)   ((xva)&0xfff) 

extern int printf(const char *format, ...);

// void mmu_test(){
//     // char *s = "mmu_test running\n";
//     while(1){
//         // s = "mmu_test running\n";
//         // while(*s != 0){
//         //     *(char *)(0xA00000) = *s++;
//         // }
//         *(char *)(0x40000000) = '6';
//     }
// }
// extern long __stack_end;
void mmu_init(void){
    
    memset((0x80010000), 0 , 512);
    printf("memset((0x80010000), 0 , 512);\n");
    // *((uint64_t *)(0x80010000)) = ((( 1 ) & 0xfffffffffff) << 10) | PTE_V;
    printf("*((uint64_t *)(0x80010000)) %x\n",0x12);

    printf("pt2 addr %x\n",0x80010000 + get_VPN2_va(0x40000000) * RV64_MMU_SV39_PTESIZE);
    
    *((uint64_t *)(0x80010000 + get_VPN2_va(0x40000000) * RV64_MMU_SV39_PTESIZE)) = ((( (0x80010000 + 1 * RV64_MMU_SV39_PAGESIZE) / RV64_MMU_SV39_PAGESIZE ) & 0xfffffffffff) << 10) | PTE_V; // 4KB page
    
    // 把 0x80000000 映射到 0x80000000
    *((uint64_t *)(0x80010000 + get_VPN2_va(0x80000000) * RV64_MMU_SV39_PTESIZE)) = (((0x80000000 >> 12) & 0xfffffffffff) << 10) | PTE_V | PTE_R | PTE_W | PTE_X; // 1GB page
    
    printf("pt3 addr %x\n",(0x80010000 + 1 * RV64_MMU_SV39_PAGESIZE) + get_VPN1_va(0x40000000) * RV64_MMU_SV39_PTESIZE);
    // 0x40000000 map to 0x92c00000
    *((uint64_t *)((0x80010000 + 1 * RV64_MMU_SV39_PAGESIZE) + get_VPN1_va(0x40000000) * RV64_MMU_SV39_PTESIZE)) = ( ((0x92c00000 >> 12) & 0xfffffffffff) << 10) | PTE_V | PTE_R | PTE_W | PTE_X;// 4KB page
    // *((uint64_t *)(0x80010000 + RV64_MMU_SV39_PAGESIZE * 2 + get_VPN1_va(0x80000000) * RV64_MMU_SV39_PTESIZE)) = ( ((0x80000000 >> 12) & 0xfffffffffff) << 10) | PTE_V | PTE_R | PTE_W | PTE_X;

    // *((uint64_t *)(0x1000C)) = ( ((uint64_t)bin_file_buf)>>12 << 10) | PTE_V | PTE_R | PTE_W | PTE_X;
    // *((uint64_t *)(0x12000)) = ((( 0 ) & 0xfffffffffff) << 10) | PTE_V | PTE_R | PTE_W | PTE_X;
    // *((uint64_t *)(0x11020)) = ((( 0 ) & 0xfffffffffff) << 10) | PTE_V | PTE_R | PTE_W | PTE_X;
    // *((uint64_t *)(0x10018)) = ( ((uint64_t)bin_file_buf+4096)>>12 << 10) | PTE_V | PTE_R | PTE_W | PTE_X;

    // *((uint64_t *)(0x10008)) = ((( 3 ) & 0xfffffffffff) << 10) | PTE_V;
    // *((uint64_t *)(0x13000)) = ((( 0xa00 ) & 0xfffffffffff) << 10) | PTE_V | PTE_R | PTE_W | PTE_X;

    
}
typedef void (*mmu_test_va_func_t)(void);
// void _vertor_func(void){
//     uint64_t mtval_v;
//     asm volatile("csrr %0, mtval":"=r"(mtval_v));
//     *(char *)(0x40000000) = '0'+((mtval_v>>60)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>56)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>52)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>48)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>44)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>40)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>36)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>32)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>28)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>24)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>20)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>16)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>12)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>8)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v>>4)&0xf);
//     *(char *)(0x40000000) = '0'+((mtval_v)&0xf);
//     *(char *)(0x40000000) = '\n';
//     *(char *)(0x40000000) = 'f';
//     asm volatile("csrw satp, %0"::"r"(0));
//     *((uint64_t *)(0x10010)) = ((( 4 ) & 0xfffffffffff) << 10) | PTE_V;
//     *((uint64_t *)(0x13400)) = ((( 0x800 ) & 0xfffffffffff) << 10) | PTE_V | PTE_R | PTE_W | PTE_X;
//     asm volatile("csrw satp, %0"::"r"(MAKE_SATP(0x10000)));
// }
// void set_vertor(void){
//     asm volatile("csrw mtvec, %0"::"r"(_vertor_func));
// }
void main(void){
    printf("mmu_test start\n");
    // mmu_test_va_func_t mmu_test_va = (mmu_test_va_func_t )((uint64_t)(mmu_test) & 0xfff);
    // printf("mmu_test %016x mmu_test_va %016lx \n",mmu_test,mmu_test_va);
    // memcpy(mmu_test_va,mmu_test,0x1000);
    mmu_init();
    // w_satp(MAKE_SATP(mmu_test_pagetable));
    asm volatile("csrw satp, %0"::"r"(MAKE_SATP(0x80010000)));
    *(char *)(0x40000000) = '6';
    printf("mmu_test pass...\n");
    // *(char *)(0x50000000) = '7';
    // mmu_test();
    // set_vertor();
    // for(uint64_t i = 0;i<sizeof(bin_file_buf)/4;i++){
    //     *((uint32_t *)(0x50000000)+i) = bin_file_buf[i];
    //     *(char *)(0x40000000) = '#';
    // }
    
    // *(char *)(0x40000000) = '7';
    // ((mmu_test_va_func_t)(0x50000000))();
    // *(char *)(0x40000000) = '8';
    // *(char *)(0x60000000) = '8';
    // *(char *)(0x80000000) = '6';
    while(1){
        // printf("hello world\r\n");
        // printf("hello world %d\n",6666666);
    }
}

int puts(const char *s){
    while(*s != 0){
        *(char *)(0x92c00000) = *s++;
    }
}
int putchar(const int c){
    *(char *)(0x92c00000) = c;
}
int _write (int fd, char *pBuffer, int size)  
{
    for (int i = 0; i < size; i++)
    {   
        *(char *)(0x92c00000) = *pBuffer++;
    }  
    return size;
}