/* Copyright 2023 Robert O'Shea
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .rodata
.align 4
gdt:
	.quad 0 # Null segment

gdt_codepl0_entry:
	.set gdt_codepl0_seg, gdt_codepl0_entry - gdt 	
	.quad 0xcf9a000000ffff

gdt_datapl0_entry:
  	.set gdt_datapl0_seg, gdt_datapl0_entry - gdt
	.quad 0xcf92000000ffff

gdt_codepl3_entry:
	.set gdt_codepl3_seg, gdt_codepl3_entry - gdt 	
	.quad 0xcffa000000ffff

gdt_datapl3_entry:
  	.set gdt_datapl3_seg, gdt_datapl3_entry - gdt
	.quad 0xcff2000000ffff

gdt_pointer:
	.set gdt_limit, gdt_pointer - gdt - 1
	.word gdt_limit
	.long gdt

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Load the GDT.
	lgdt (gdt_pointer)
	
	mov $gdt_datapl0_seg, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

	ljmp $gdt_codepl0_seg, $kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
