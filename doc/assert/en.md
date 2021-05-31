![JUICE VM](./doc/assert/logo.png)                                                 


   * [Introduction](#introduction)
   * [The Advantage of Juice Vm](#the-advantage-of-juice-vm)
   * [The feature of  Juice Vm](#the-feature-of--juice-vm)
   * [Juice Vm's statistics](#juice-vms-statistics)
   * [Juice Vm's address](#juice-vms-address)
   * [The software process of Project](#the-software-process-of-project)
   * [Get started](#get-started)
   * [<strong>Example</strong>](#example)
   * [The Shot of freertos](#the-shot-of-freertos)
   * [The Shot of rt-thread](#the-shot-of-rt-thread)
   * [The Shot of linx 5.0.0](#the-shot-of-linx-500)
   * [<strong>Parameters Specification</strong>](#parameters-specification)
* [Community support](#community-support)
   * [<strong>CHANGE LOG</strong>](#change-log)
      * [<strong>2021-05-25</strong>](#2021-05-25)
      * [<strong>20210524 juice_vm_release_for_Linux_c21682d3.zip：</strong>](#20210524-juice_vm_release_for_linux_c21682d3zip)
      * [<strong>20210508：</strong>](#20210508)
      * [<strong>20210427：</strong>](#20210427)
      * [<strong>2021042:</strong>](#2021042)
         * [<strong>software specification</strong>](#software-specification)
         * [<strong>Update parameters：</strong>](#update-parameters)
      * [<strong>202210306:</strong>](#202210306)
         * [<strong>software specification</strong>](#software-specification-1)
         * [<strong>Update parameters:</strong>](#update-parameters-1)
         * [<strong>Issue</strong>](#issue)
      * [2021-03-06 :](#2021-03-06-)
         * [<strong>Update Parameters:</strong>](#update-parameters-2)
         * [<em>Software Specification</em>*](#software-specification-2)
* [Thanks](#thanks)
* [Contact us](#contact-us)




## Introduction
The project began in 2020.Juice Vm is a small RISC-V virtual machine and run the latest kernel.The chip which contain hundreds of KB RAM can run this virtual machine,but it wouldn't contain any third-party libraries. 

Juice Vm follow gcc C99 stardard,without any third-party library.Therefore,it is really easy to read and it support many platforms.


There is only  **12523** lines and  **36104** words in  the project without any annotation .Therefore it is really small.


## The Advantage of Juice Vm

- Consume  little memory

- Support some platforms easily.


## The feature of  Juice Vm
 - ISA(Instruction Set Architecture)：RV64IMASU.
 - Suport mtime in M-mode,U-mode,S-mode
 - Super small uart,only contain two Register:read and write
 - Super samll MMU(support SV39)
 - Support exception and interruption with official RISC-V stardard

## Juice Vm's statistics
![JUICE VM](./doc/assert/juicevm_size.png) 

## Juice Vm's address

| Version | Start Address | Size(Byte) | Register | Statement  | Macro definition |
| :-----------: | :-------- | :------- | :------- | :------------| :------------ |
| c21682d3 | 0x80000000 | 0x12C00000 | SRAM | internal storage | RV_CPU_SIM_RAM_START_ADDR RV_CPU_SIM_RAM_SIZE |
| c21682d3 | 0x92C00000 | 0x1 | UART_WRITE | uart send register | pdev_uart0_write_addr |
| c21682d3 | 0x92C00001 | 0x1 | UART_READ | uart recv register | pdev_uart0_read_addr |
| c21682d3 | 0x92C00002 | 0x1 | UART_STATE | uart state register | pdev_uart0_state_addr pdev_uart0_free_state pdev_uart0_readbusy_state |
| c21682d3 | 0x92C00003 | 0x8 | mtime | current count register | pdev_mtime_mtime_addr |
| c21682d3 | 0x92c00007 | 0x8 | mtimecmp | compare register | pdev_mtime_mtimecmp_addr |


## The software process of Project
- Support the C program
- Support freertos
- Support mbedtls
- Pass mmu sv39 test
- Pass mtime test
- Support opensbi [Link](https://github.com/juiceRv/opensbi_juicevm_port)
- Support rt-thread ,Thanks for @熊大和@Andy Chen  [Link](https://github.com/RT-Thread/rt-thread/tree/master/bsp/juicevm)
- Support kernel 5.0.0 [Link](https://github.com/juiceRv/kernel_juicevm_port)
- Upload GCC toolchain [Link](https://github.com/juiceRv/gcc-gnu-toolchains-for-juicevm)
- Support GDB **TODO**
- SUpport RT-SMART **TODO**
-


## Get started
- **UBUNTU/DEBIAN** APT install 
```
    echo "deb http://xiaohui.mongoyun.com:3333/ trusty main" | sudo tee -a /etc/apt/sources.list
    wget -O - http://xiaohui.mongoyun.com:3333/key/deb.gpg.key | sudo apt-key add -
    sudo apt update
    sudo apt install juicevm
    juicevm
```
- **CENTOS**
```
    echo "deb http://xiaohui.mongoyun.com:3333/ trusty main" | sudo tee -a /etc/apt/sources.list
    wget -O juice_vm_release_for_Linux_laster.zip https://github.com/juiceRv/JuiceVm/raw/master/juice_vm_release_for_Linux_laster.zip
    unzip juice_vm_release_for_Linux_laster.zip
    cd juice_vm_release_for_Linux_c21682d3/juice_vm_release_for_Linux
    sudo chmod +x juice_vm_for_Linux.out
    ./juice_vm_for_Linux.out
```
- **WINDOW**

**Compile**
## **Example**
- [Hello world](./doc/get-started.md) **todo**
- [Free rtos](./doc/run-freertos.md) **todo**
- [mbedtls](./doc/run-mbedtls.md) **todo**
- [SV39 MMU test](./doc/run-mmu_sv39.md) **todo**
- [mtime test](./doc/run-mmu_sv39.md) *todo**
- [mtime test](./doc/run-mtime.md) **todo**
- [RT-thread](./doc/run-rtt.md) **todo**
- [linux kernel](./doc/run-linux.md) **todo**

## The Shot of freertos
![JUICE VM FreeRtos](./doc/assert/freertos.png)

## The Shot of rt-thread
![JUICE VM RT-thread](./doc/assert/juicevm_rtt.jpg)

## The Shot of linx 5.0.0
![JUICE VM linux kernel](./doc/assert/juicevm_kernel.png)

## **Parameters Specification**
| Parm | Name | statement |
| :------ | :------- | :-------|
| t | enable test mode | Enter test mode<br>When appearing the following statement,the machine would end up,x3_gp register's value is **1** and  x17_a7 register's vaule is 93时,it cause ecall exception。when x10_a0 register's value is 0 ,it print pass，otherwise it print "faile" |
| **T** | enable trap debug mode | enable exception mode and it will print current exception information |
| d | enable debug mode | Open all debug option in vitural machine and print debug ,include ISA,running process,register list ,csr list and etc. |
| c | print cst operation msg | enable debug csr register(read and write register) and print all the register values. |
| a | diable all debug msg | Disable all debug message |
| x | enable test mode for exception | It caused by exception |
| g | enable better readability printing | None |
| e | disable all error msg | None |
| i | enable all instr debug msg | None |
| m | enable mmu debug msg | None |
| p | print mmu page 8 byte data | None |
| **P** | print mmu page 4K Byte data | None |
| s | uart addr not use mmu translation | Enalbe mmu translation,and ignore uart address.Control the uart by read and write uart physical address when enble mmu |
| **S** | switch mode debug info | enable debug when switching the mode.It print debug information in m-mode,s-mode and u-mode |
| **M** | disable mmu err msg | Disable debug about Page missing,exception  |
| r | enable trap debug msg | Print more detailed debug about interruption |
| **A** | enable addr translation debug print | None |
| **L**(n) | log mode | output_mode_sel n = 0 -> stdout<br> 1 -> log_buf UNIX SYS ONLY(buf_size:(2900))<br> 2 -> none<br> Choose output mode，1，stardard ouput. 2，Store in a buffer when the code is running.Ouput 2900Byte buffer when the code exit. 3，No ouput。<br> |
| l | enable endless loop check (RV_ENDLESS_LOOP_CHECK_EXIT_CNT:(3)) | Enable loop watcher,when it run the same introduction three times continuously(include registers and csr register value wouldn't change),end the vm.You can run the vm with -L in order to debug the fireware.It would be bad loop when show assert  |


# Community support
    Thanks for whycan  ：[https://whycan.com/t_5844.html](https://whycan.com/t_5844.html)

## **CHANGE LOG**
### **2021-05-25**
- The codes of opensbi and kernel are published in github
[https://github.com/juiceRv/kernel_juicevm_port](https://github.com/juiceRv/kernel_juicevm_port)
kernel configuration :arch/riscv/configs/juicevm_defconfig,make ARCH=riscv juicevm_defconfig  
- Please open  file (arch/riscv/configs/juicevm_defconfig) and modify **CONFIG_INITRAMFS_SOURCE** (the real opensbi path )  

    opensbi  
    [https://github.com/juiceRv/opensbi_juicevm_port](https://github.com/juiceRv/opensbi_juicevm_port)

    toolchains  
    [https://github.com/juiceRv/gcc-gnu-toolchains-for-juicevm](https://github.com/juiceRv/gcc-gnu-toolchains-for-juicevm)

***

### **20210524 juice_vm_release_for_Linux_c21682d3.zip：**
1. fix mtime interruption bug in m-mode,s-mode and u-mode
2. fix ecall bug in s-mode 
3. fix issue about interruption in s-mode and u-mode,fix  the csr register.
4. support linux(5.0.0)

***

### **20210508：**
1. release the package in ubuntu20.04,thanks for @XBOOT
1. support div introduction set
3. fix divuw，divw，remu，remw，amomin.w，amoswap.w introduction error


***
### **20210427：**
    Support RT-Thread OS ,please refer: https://github.com/RT-Thread/rt-thread/tree/master/bsp/juicevm
***

### **2021042:**
#### **software specification**
1.Support rt-thread

#### **Update parameters：**
1. -L:Support different output mode with 
2. -l:End the code when the machine enter bad loop
3. -r:enalbe trace debug
4. Add Alive logo
5. -T: Print compilation information when the code is running
6. support m-mode
7. support s-mode(u-mode **todo**)


***


### **202210306:**  
#### **software specification**
1. Support c program
2. Supoort freertos
3. Support mbedtls
4. Support mmu sv39 test
5. Support mtimer test
6. Support opensbi

#### **Update parameters:**
- -m **enable mmu debug**
#### **Issue**

- 1113e998 add sfence.vma instr
- f118d476 add print instr support
- 1e3e7204 add AMOSWAP.D LR.D and SC.D instr support
- 686741ea add AMOSWAP.D LR.D and SC.D instr support
- f2f699c0 add -i arg to enable instr print support
- 113f66da add misa csr support
- 19cf60d1 fix divu err
- ad512e54 add divu remw and remu instr
- 9abc0566 fix mem overflow
- 0ceb663e fix divw instr and add REMW instr
- 10a2ea78 fix divw instr
- 9c93c4ce add amoswap.w , mul and divw instr
- df10ad45 change the fireware start addr to 0x80000000
- d31b4ac1 add amoadd.w inst

***

###  2021-03-06 :

finish risc-v vitual machine with muc and there is within 5000 lines c codes.


Base bu rv64i

Support mtime，small uart and mmu sv39.

#### **Update Parameters:**
- -a **close all debug**
- -e **close error debug**
- -g **format print**
- -d **enable all debug (include register and csr list)**
- -i **enalbe decode debug**
- -m **enable mmu debug**

#### *Software Specification**
1. Support c program
2. Supoort freertos
3. Support mbedtls
4. Support mmu sv39 test
5. Support mtimer test
6. Support opensbi

# Thanks
- [哇酷网](https://whycan.com/t_5844.html)
- [RT-thread](https://www.rt-thread.io/)
- [RISC-V](https://riscv.org/)
- [linux](https://www.kernel.org/)
- [gh-md-toc](https://github.com/ekalinin/github-markdown-toc)
    
# Contact us
juicemail@163.com