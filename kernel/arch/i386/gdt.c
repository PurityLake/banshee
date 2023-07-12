#include <kernel/gdt.h>

extern const gdtr_t gdtr;

static uint64_t create_gdt_descriptor(uint32_t base, uint32_t limit,
                                      uint16_t flag);

void
init_gdt(void)
{
  static int initialized = 0;
  if(initialized)
  {
    return;
  }

  asm("cli");

  uint64_t *gdt = (uint64_t *)gdtr.base;
  // null descriptor
  *gdt = create_gdt_descriptor(0, 0, 0);
  // PL0 code descriptor
  *(gdt + 1) = create_gdt_descriptor(0, 0x000FFFFF, ((GDT_CODE_PL0)));
  // PL0 data descriptor
  *(gdt + 2) = create_gdt_descriptor(0, 0x000FFFFF, ((GDT_DATA_PL0)));
  // PL3 code descriptor
  *(gdt + 3) = create_gdt_descriptor(0, 0x000FFFFF, ((GDT_CODE_PL3)));
  // PL3 data descriptor
  *(gdt + 4) = create_gdt_descriptor(0, 0x000FFFFF, ((GDT_DATA_PL3)));

  asm("lgdt (gdtr)");

  asm("ljmp $0x08, $next\n"
      "next:           \n"
      "mov $0x10, %ax  \n"
      "mov %ax, %ds    \n"
      "mov %ax, %es    \n"
      "mov %ax, %fs    \n"
      "mov %ax, %gs    \n"
      "mov %ax, %ss    \n"
      "ret");
}

static uint64_t
create_gdt_descriptor(uint32_t base, uint32_t limit, uint16_t flag)
{
  uint64_t descriptor;

  // Create the high 32 bit segment
  descriptor = limit & 0x000F0000; // set limit bits 19:16
  descriptor |= (flag << 8)
                & 0x00F0FF00; // set type, p, dpl, s, g, d/b, l and avl fields
  descriptor |= (base >> 16) & 0x000000FF; // set base bits 23:16
  descriptor |= base & 0xFF000000;         // set base bits 31:24

  // Shift by 32 to allow for low part of segment
  descriptor <<= 32;

  // Create the low 32 bit segment
  descriptor |= base << 16;         // set base bits 15:0
  descriptor |= limit & 0x0000FFFF; // set limit bits 15:0

  return descriptor;
}
