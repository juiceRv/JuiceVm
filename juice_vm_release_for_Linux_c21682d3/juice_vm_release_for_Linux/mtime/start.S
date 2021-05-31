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
    addi s2, x0, 'a';
    li  t1, pdev_uart0_write_addr;
    sb s2,0(t1);

    addi s2, x0, 'b';
    li  t1, pdev_uart0_write_addr;
    sb s2,0(t1);

    addi s2, x0, '\n';
    li  t1, pdev_uart0_write_addr;
    sb s2,0(t1);
    
    j reset_vector
    .align  4;                                             
reset_vector:
    addi s2, x0, 'r';
    li  t1, pdev_uart0_write_addr;
    sb s2,0(t1);

    addi s2, x0, '\n';
    li  t1, pdev_uart0_write_addr;
    sb s2,0(t1);
    
    la a0,e_vertor;

    addi s2, x0, 300;
    li  t1, pdev_mtime_mtimecmp_addr;
    sd s2,0(t1);

    csrw mtvec,a0;
    # set mstatus.MIE=1 (enable M mode interrupt)
    li      t0, 8
    csrrs   zero, mstatus, t0

    # set mie.MTIE=1 (enable M mode timer interrupt)
    li      t0, 0x80
    csrrs   zero, mie, t0

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

    call main;
    j _start;


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
    li  t1, pdev_uart0_write_addr;
    sb s2,0(t1);

    csrr a0,mcause
    call execption_handle;

    # set mie.MTIE=1 (enable M mode timer interrupt)
    # li      t0, 0x80
    # csrrs   zero, mie, t0

    csrrc  t0, mcause, zero
    mret;



.data
