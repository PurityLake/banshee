#include <kernel/port.h>

unsigned char
inb(uint16_t port)
{
  unsigned char result;
  asm volatile("in %%dx, %%al" : "=a"(result) : "d"(port) : "memory");
  return result;
}

void
outb(uint16_t port, unsigned char data)
{
  asm volatile("out %%al, %%dx" : : "a"(data), "d"(port) : "memory");
}
