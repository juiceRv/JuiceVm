.PHONY:all clean
CROSS_COMPILE?=riscv64-unknown-elf-
#CROSS_COMPILE?=../../tools/riscv64-unknown-elf-gcc-8.2.0-2019.05.3-x86_64-w64-mingw32/bin/riscv64-unknown-elf-
PRJ_NAME  ?=freertos

AS 		:= $(CROSS_COMPILE)gcc -x assembler-with-cpp
CC 		:= $(CROSS_COMPILE)gcc
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
LD		:= $(CROSS_COMPILE)ld

CFLAGS  	:= -march=rv64i -static -DportasmHANDLE_INTERRUPT=vApplicationHandleTrap -mabi=lp64 -I ../../ -I . -I Source/include -nostartfiles -mcmodel=medany -ffunction-sections -fdata-sections
OBJFLASGS 	:= --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data

#CFLAGS      += -fbuilding-libgcc -g -ffreestanding -lgcc -L="../../../../riscv64-unknown-elf-gcc-8.3.0-2020.04.0-x86_64-linux-ubuntu14/lib/gcc/riscv64-unknown-elf/8.3.0/rv64i/lp64/"

CFLAGS      += -D__riscv_xlen=64 -D__riscv64

LDFLAGS     := -T$(PRJ_NAME)_link.ld
#LDFLAGS     += -lgcc -L="../../../../riscv64-unknown-elf-gcc-8.3.0-2020.04.0-x86_64-linux-ubuntu14/lib/gcc/riscv64-unknown-elf/8.3.0/rv64i/lp64/"
#LDFLAGS     += -L="../../../../riscv64-unknown-elf-gcc-8.3.0-2020.04.0-x86_64-linux-ubuntu14/lib/gcc/riscv64-unknown-elf/8.3.0/rv64i/lp64/"

SRC_PATH   := Source

SRCS       := port.c main.c printf-stdarg.c main_blinky.c
SRCS       += $(wildcard $(SRC_PATH)/*.c)
SRCS       += Source/portable/MemMang/heap_1.c
ASMS       := start.S portASM.S
OBJS       := $(SRCS:.c=.o)
OBJ        := $(ASMS:.S=.o)

LINK_OBJS += $(OBJS) $(OBJ)

all: $(PRJ_NAME).bin $(PRJ_NAME)_dump.s

$(OBJ): %.o : %.S
	@echo [AS] $<
	@$(AS) $(CFLAGS) -c $< -o $@

$(OBJS): %.o:%.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(PRJ_NAME):$(OBJ) $(OBJS) 
	@echo [LD] Linking $@
	$(CC) $(CFLAGS) $(LINK_OBJS) -o $@ $(LDFLAGS)

$(PRJ_NAME).bin:$(PRJ_NAME)
	@echo [LD] Linking $@
	@$(OBJCOPY) -O binary $< $@

$(PRJ_NAME)_dump.s:$(PRJ_NAME)
	@echo [OD] Objdump $@ $<
	@$(OBJDUMP) $(OBJFLASGS) $< > $@

clean:
	rm $(OBJS) $(OBJ) $(PRJ_NAME).bin $(PRJ_NAME) $(PRJ_NAME).map $(PRJ_NAME)_dump.s
