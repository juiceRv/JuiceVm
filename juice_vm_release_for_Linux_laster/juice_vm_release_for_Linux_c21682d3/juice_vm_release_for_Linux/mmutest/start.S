    #include "rv_mtvec_map.h"
    .macro init;
    .endm
    .section .text.init;
    .option norvc
    .option nopic
    .align  6;
    .weak reset_vector;
    .globl _start;
_start:
    la sp, __stack_end                                    
    /* reset vector */
    # addi s2, x0, 'a';
    # li  t1, 0xA00000;
    # sb s2,0(t1);

    # addi s2, x0, 'b';
    # li  t1, 0xA00000;
    # sb s2,0(t1);

    # addi s2, x0, '\n';
    # li  t1, 0xA00000;
    # sb s2,0(t1);

2:
	/* Clear bss section */
	la a0, __bss_start;
	la a1, __bss_end;
	bgeu a0, a1, 2f;
1:
	sw zero, (a0);
	addi a0, a0, 4;
	bltu a0, a1, 1b;
2:
    la a0,e_vertor;
    csrw mtvec,a0;
    call main;
    # j _start;
    .align  4;                                             
reset_vector:
    addi s2, x0, 'r';
    li  t1, 0xA00000;
    sb s2,0(t1);

    # addi s2, x0, '\n';
    # li  t1, 0xA00000;
    # sb s2,0(t1);
    
    la a0,e_vertor;
    csrw mtvec,a0;
    # set mstatus.MIE=1 (enable M mode interrupt)
    li      t0, 8
    csrrs   zero, mstatus, t0

1:  fence;
2:  wfi;
    j 2b;
    li	gp,1;
    li	a7,93;
    li	a0,0;
    ecall;
    # mret;
    unimp
e_vertor:
    addi s2, x0, 'e';
    li  t1, 0x40000000;
    sb s2,0(t1);

    csrrc  t0, mcause, zero
    mret;



.data
