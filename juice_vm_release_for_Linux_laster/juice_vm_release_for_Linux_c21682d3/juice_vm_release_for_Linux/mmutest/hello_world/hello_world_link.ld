OUTPUT_ARCH(riscv)
ENTRY(_start)
MEMORY
{
	ram  : org = 0x50000000, len = 4K
}

SECTIONS
{
	.text :
	{
		*(.text.main)
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
	_end = .; PROVIDE (end = .);
	PROVIDE( __global_pointer$ = . + (4K / 2) );
	_edata = .; PROVIDE (edata = .);
	
  	PROVIDE(__stack_end = 0x50000000+4K);
}
