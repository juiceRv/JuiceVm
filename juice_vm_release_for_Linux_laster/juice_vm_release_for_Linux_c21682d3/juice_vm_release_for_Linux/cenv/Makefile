.PHONY:all clean
CROSS_COMPILE?=riscv64-unknown-elf-
PRJ_NAME  ?=c_env_test

AS 		:= $(CROSS_COMPILE)gcc -x assembler-with-cpp
CC 		:= $(CROSS_COMPILE)gcc
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
LD		:= $(CROSS_COMPILE)ld

CFLAGS  	:= -std=gnu99 -march=rv64i -mabi=lp64 -I ../../ -mcmodel=medany -ffunction-sections -fdata-sections 
OBJFLASGS 	:= --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data

LDFLAGS     := -T $(PRJ_NAME)_link.ld

SRC_PATH   := .
SRCS       := $(wildcard $(SRC_PATH)/*.c)
ASMS       := $(wildcard $(SRC_PATH)/*.S)
OBJS       := $(SRCS:.c=.o)
OBJ        := $(ASMS:.S=.o)

all: $(PRJ_NAME).bin $(PRJ_NAME)_dump.s

$(OBJ) : %.o : %.S
	@echo [AS] $<
	@$(AS) $(CFLAGS) -c $< -o $@

$(OBJS) : %.o:%.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(PRJ_NAME):$(OBJ) $(OBJS) 
	@echo [LD] Linking $@
	@$(LD) $(LDFLAGS) $^ -o $@

$(PRJ_NAME).bin:$(PRJ_NAME)
	@echo [LD] Linking $@
	@$(OBJCOPY) -O binary $< $@

$(PRJ_NAME)_dump.s:$(PRJ_NAME)
	@echo [OD] Objdump $@ $<
	@$(OBJDUMP) $(OBJFLASGS) $< > $@

clean:
	rm $(OBJS) $(OBJ) $(PRJ_NAME).bin $(PRJ_NAME) $(PRJ_NAME).map $(PRJ_NAME)_dump.s
