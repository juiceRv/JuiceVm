.PHONY:all clean

CROSS_COMPILE?=riscv64-unknown-elf-

AS 		:= $(CROSS_COMPILE)gcc -x assembler-with-cpp
CC 		:= $(CROSS_COMPILE)gcc
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
LD		:= $(CROSS_COMPILE)ld

CFLAGS  	:= -nostartfiles -march=rv64i -static -mabi=lp64  -mcmodel=medany -ffunction-sections -fdata-sections
OBJFLASGS 	:= --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
LDFLAGS     := -T hello_world_link.ld

all: 
	$(CC) $(CFLAGS) -c hello_world.c -o hello_world.o
	$(LD) -e main hello_world.o -o hello_world $(LDFLAGS)
	@$(OBJCOPY) -O binary hello_world hello_world.bin
	@$(OBJDUMP) $(OBJFLASGS) hello_world > hello_world_dump.s

clean:
	rm hello_world hello_world.bin hello_world_dump.s hello_world.o
