OUTPUT_ARCH(riscv)
ENTRY(_start)
MEMORY
{
	ram  : org = 0x80000000, len = 10M
}

SECTIONS
{
	.text :
	{
		*(.text*)
	} > ram

	.data ALIGN(8) :
	{
		*(.data*)
    	*(.rodata*)
		. = ALIGN(8);
	} > ram

	PROVIDE(__bss_start = .);
	.bss ALIGN(8) (NOLOAD) :
	{
		*(.bss*)
		. = ALIGN(8);
	} > ram
	PROVIDE(__bss_end = .);

  PROVIDE(__stack_end = 0x80000000+1M);
}
