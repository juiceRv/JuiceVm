![JUICE VM](./doc/assert/logo.png)                                                 
                                                                
## 简介
juice vm诞生于2020年，以实现可运行最新kernel主线的RISC-V最小虚拟机为目标而诞生的，设计之初秉承着可以在 **RAM** 只有 **百KB** 级别的平台上运行，不引入除了**c99**标准外的第三方依赖。

juice vm按照gcc所支持的C99标准编写，无第三方库依赖，浅显易懂，且具有方便移植的特性（可快速移植到多种主流 MCU 及支持c环境的所有平台上）。

juice vm去掉注释后展开所有的宏的代码行数仅**12523**行，仅**36104**字，足够的小巧。

## Juice Vm的特点

- 资源占用极低。

- 跨平台、可快速移植。

## Juice Vm的组成
 - 指令集：RV64IMASU.
 - 支持了M-mode,U-mode,S-mode下的mtime.
 - 超级精简的uart，只有读和写两个外设寄存器.
 - 超级精简的MMU SV39支持.
 - 支持RISC-V官方标准的异常和中断托管

## Juice Vm下的软件移植进度
- 已经支持了c语言编程。
- 已完成freertos移植。
- 已完成mbedtls移植。
- 已完成mmu sv39测试。
- 已完成mtime测试。
- 已完成opensbi移植 [传送门](https://github.com/juiceRv/opensbi_juicevm_port)。
- 已完成rt-thread移植，感谢@熊大和@Andy Chen的支持 [传送门](https://github.com/RT-Thread/rt-thread/tree/master/bsp/juicevm)。
- 已完成kernel主线5.0.0 [传送门](https://github.com/juiceRv/kernel_juicevm_port)。
- 上传Juice Vm下的GCC toolchain [传送门](https://github.com/juiceRv/gcc-gnu-toolchains-for-juicevm)。
- 适配 GDB 通用接口支持 **TODO**。
- 适配 RT-SMART **TODO**。

## **快速上手**
    [快速上手运行Hello world](./doc/get-started.md) **编写中**。
    [运行Free rtos](./doc/run-freertos.md) **编写中**。
    [运行mbedtls](./doc/run-mbedtls.md) **编写中**。
    [运行SV39 MMU测试](./doc/run-mmu_sv39.md) **编写中**。
    [运行mtime测试](./doc/run-mmu_sv39.md) **编写中**。
    [运行mtime测试](./doc/run-mtime.md) **编写中**。
    [运行 RT-thread](./doc/run-rtt.md) **编写中**。
    [运行 linux kernel](./doc/run-linux.md) **编写中**。